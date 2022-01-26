#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define GNL_BUFFER_SIZE 256
# define GNL_ERROR -1
# define GNL_EOF 0
# define GNL_CONTINUE 1

typedef struct s_gnl
{
	char	*ptr;
	char	*read_str;
	ssize_t	read_len;
	ssize_t	valid_len;
	ssize_t	offset;
	int		flag;
	int		times;
}t_gnl;

ssize_t	count_valid_len(const char *str, ssize_t len);
char	*copy_free(char *dst, char *src, ssize_t len, ssize_t idx);
char	*ft_strndup(char *src, ssize_t len);
char	*allocate_line(ssize_t len);
void	is_end(t_gnl *gnl);
char	*rec_gnl(ssize_t i, t_gnl *gnl, int fd);
void	put_away_line(t_gnl *gnl);
int		get_next_line(int fd, char **line);

void	*xmalloc(size_t size);
size_t	ft_strlen(const char *str);
char	**ft_split(char *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *str);
void	xput_error(char *str);

#endif
