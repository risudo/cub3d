/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:39:49 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/05 21:25:26 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# ifdef __linux
#  define MOVE_SPEED 0.05
#  define ROTATE_SPEED 0.03
# else
#  define MOVE_SPEED 0.1
#  define ROTATE_SPEED 0.05235987755982988
# endif
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define CLIENT_MESSAGE 33
# define KEY_PRESS_MASK 1L
# define KEY_RELEASE_MASK 2L
# define STRUCTURE_NOTIFY_MASK 131072
# define INF 2147483647
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define PITCH 100
# define X_SIDE 0
# define Y_SIDE 1

# ifndef M_PI
#  define M_PI 3.1415926535
# endif
# ifndef M_PI_2
#  define M_PI_2 1.570796326
# endif

#endif
