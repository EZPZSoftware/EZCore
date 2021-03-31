/*
 EZCore - chmod utility
 by amdbtw
*/

#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>

#define PATH_LEN 4096

const char *options = "R";
char *ourname;

void usage()
{
  printf("Usage: %s [-R] mode file\n", ourname);

  exit(0);
}

void error(char *msg) {
  fprintf(stderr, "%s: %s: %s\n", ourname, msg, strerror(errno));

  exit(1);
}

struct out_mode_entry_s {
  bool r;
  bool w;
  bool x;
};

typedef struct {
  struct out_mode_entry_s u;
  struct out_mode_entry_s g;
  struct out_mode_entry_s o;
} our_mode_t;

#define OUT_MODE_NEW_ENTRY(entry, mode) m->entry = (s.st_mode & mode) ? true : false;
our_mode_t *out_mode_new(char *filename) {
  our_mode_t *m = malloc(sizeof(our_mode_t));
  struct stat s;
  if(stat(filename, &s) < 0)
  {
    error("cannot read current stat of file");
  }

  OUT_MODE_NEW_ENTRY(u.r, S_IRUSR)
  OUT_MODE_NEW_ENTRY(u.w, S_IWUSR)
  OUT_MODE_NEW_ENTRY(u.x, S_IXUSR)
  OUT_MODE_NEW_ENTRY(g.r, S_IRGRP)
  OUT_MODE_NEW_ENTRY(g.w, S_IWGRP)
  OUT_MODE_NEW_ENTRY(g.x, S_IXGRP)
  OUT_MODE_NEW_ENTRY(o.r, S_IROTH)
  OUT_MODE_NEW_ENTRY(o.w, S_IWOTH)
  OUT_MODE_NEW_ENTRY(o.x, S_IXOTH)

  return m;
}

#define OUR_MODE_GENMODE_ENTRY(entry, mode) \
  if(m->entry) \
  { \
    ret |= mode; \
  }
mode_t our_mode_genmode(our_mode_t *m) {
  mode_t ret = 0000;

  OUR_MODE_GENMODE_ENTRY(u.r, S_IRUSR)
  OUR_MODE_GENMODE_ENTRY(u.w, S_IWUSR)
  OUR_MODE_GENMODE_ENTRY(u.x, S_IXUSR)
  OUR_MODE_GENMODE_ENTRY(g.r, S_IRGRP)
  OUR_MODE_GENMODE_ENTRY(g.w, S_IWGRP)
  OUR_MODE_GENMODE_ENTRY(g.x, S_IXGRP)
  OUR_MODE_GENMODE_ENTRY(o.r, S_IROTH)
  OUR_MODE_GENMODE_ENTRY(o.w, S_IWOTH)
  OUR_MODE_GENMODE_ENTRY(o.x, S_IXOTH)

  return ret;
}

#define PARSE_MODE_ENTRY(mod, entry) \
  if(mode[i] == mod) { \
    m->entry = true; \
  } \
  i++;
#define PARSE_MODE_add(entry) \
  if(u) { \
    if(entry) \
    { \
      m->u.entry = true; \
    } \
  } \
  if(g) { \
    if(entry) \
    { \
      m->g.entry = true; \
    } \
  } \
  if(o) { \
    if(entry) \
    { \
      m->o.entry = true; \
    } \
  }
#define PARSE_MODE_rem(entry) \
  if(u) { \
    if(entry) \
    { \
      m->u.entry = false; \
    } \
  } \
  if(g) { \
    if(entry) \
    { \
      m->g.entry = false; \
    } \
  } \
  if(o) { \
    if(entry) \
    { \
      m->o.entry = false; \
    } \
  }
#define PARSE_MODE_set(entry) \
  if(u) { \
    if(m->u.entry && !entry) \
    { \
      m->u.entry = false; \
    } else if(entry) \
    { \
      m->u.entry = true; \
    } \
  } \
  if(g) \
  { \
    if(m->g.entry && !entry) \
    { \
      m->g.entry = false; \
    } else if(entry) \
    { \
      m->g.entry = true; \
    } \
  } \
  if(o) \
  { \
    if(m->o.entry && !entry) \
    { \
      m->o.entry = false; \
    } else if(entry) \
    { \
      m->o.entry = true; \
    } \
  }
#define PARSE_MODE_SIMPLE(action) \
  if(action) \
  { \
    PARSE_MODE_##action(r) \
    PARSE_MODE_##action(w) \
    PARSE_MODE_##action(x) \
  }
mode_t parse_mode(char *filename, char *mode)
{
  mode_t ret = 0000;
  bool is_already = true;
  our_mode_t *m = out_mode_new(filename);

  for(int i = 0; mode[i]; i++)
  {
    if(!isdigit(mode[i]))
    {
      is_already = false;
    }
  }

  if(is_already)
  {
    ret = strtoul(mode, 0, 8);
    free(m);
    return ret;
  }

  if(strlen(mode) == 9)
  {
    int i = 0;
    PARSE_MODE_ENTRY('r', u.r)
    PARSE_MODE_ENTRY('w', u.w)
    PARSE_MODE_ENTRY('x', u.x)
    PARSE_MODE_ENTRY('r', g.r)
    PARSE_MODE_ENTRY('w', g.w)
    PARSE_MODE_ENTRY('x', g.x)
    PARSE_MODE_ENTRY('r', o.r)
    PARSE_MODE_ENTRY('w', o.w)
    PARSE_MODE_ENTRY('x', o.x)
  } else {
    bool add = false;
    bool rem = false;
    bool set = false;
    bool u = false;
    bool g = false;
    bool o = false;
    bool r = false;
    bool w = false;
    bool x = false;

    for(int i = 0; mode[i]; i++)
    {
      switch(mode[i])
      {
        case '+':
          add = true;
        break;
        case '-':
          rem = true;
        break;
        case '=':
          set = true;
        break;
        case 'u':
          u = true;
        break;
        case 'g':
          g = true;
        break;
        case 'o':
          o = true;
        break;
        case 'r':
          r = true;
        break;
        case 'w':
          w = true;
        break;
        case 'x':
          x = true;
      }
    }

    if(!u &&
      !g &&
      !o)
    {
      u = true;
    }

    PARSE_MODE_SIMPLE(set)
    PARSE_MODE_SIMPLE(add)
    PARSE_MODE_SIMPLE(rem)
  }

  ret = our_mode_genmode(m);
  free(m);
  return ret;
}

void recur(char *path, mode_t mode)
{
  DIR *dir;
  struct dirent *entry;
  char p[PATH_LEN];

  if(!(dir = opendir(path)))
  {
    error("cannot open directory");
  }

  while((entry = readdir(dir)) != NULL)
  {
    if(entry->d_type == DT_DIR){
      if(strcmp(entry->d_name, ".") == 0 ||
        strcmp(entry->d_name, "..") == 0)
      {
        continue;
      }

      snprintf(p, PATH_LEN, "%s/%s", path, entry->d_name);
      if(chmod(p, mode) != 0)
      {
        error("cannot chmod()");
      }
      recur(p, mode);
    } else
    {
      snprintf(p, PATH_LEN, "%s/%s", path, entry->d_name);

      if(chmod(p, mode) != 0)
      {
        error("cannot chmod()");
      }
    }
  }
}

int main(int argc, char **argv)
{
  bool is_r = false;
  char mode[10] = { 0 };
  char *filename;
  mode_t m;
  int i = 1;

  for(; i < argc - 1; i++)
  {
    if(strncmp(argv[i], "-R", 2) == 0)
    {
      is_r = true;
      continue;
    }

    strcat(mode, argv[i]);
  }

  filename = argv[i];
  ourname = argv[0];

  if(!mode[0] ||
    !filename ||
    strncmp(filename, "-R", 2) == 0)
  {
    usage();
  }

  m = parse_mode(filename, mode);

  if(chmod(filename, m) != 0)
  {
    error("cannot chmod()");
  }

  if(is_r)
  {
    recur(filename, m);
  }

  return 0;
}
