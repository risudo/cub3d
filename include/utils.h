/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:39:51 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/03 17:39:51 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# define GNL_BUFFER_SIZE 256
# define GNL_ERROR -1
# define GNL_EOF 0
# define GNL_CONTINUE 1

# include <stdlib.h>
# include <unistd.h>

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
char	*ft_strrchr(const char *s, int c);
char	**ft_split(char *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *str);
void	xput_error(char *str);
void	clear_string_array(char **arr);
char	**duplicate_map(char **map);

void	*mlx_xinit(void);
void	*mlx_xnew_window(void *mlx_ptr, int x, int y, char *title);
void	*mlx_xnew_image(void *mlx_ptr, int width, int height);
void	*mlx_xxpm_file_to_image(void *mlx_ptr, \
			char *filename, int *width, int *height);
#endif
