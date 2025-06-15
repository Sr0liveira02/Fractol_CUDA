/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:45:49 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/15 00:11:29 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# ifndef HIGHT
#  define HIGHT 1000
# endif
# ifndef WIDTH
#  define WIDTH HIGHT * 2.65 / 2.5
# endif

#include "mlx_linux/mlx_int.h"
#include "mlx_linux/mlx.h"
#include "my_libft/libft.h"
#include <math.h>

typedef struct s_comp
{
	double	real;
	double	i;
}	t_comp;

typedef struct s_image
{
	int		bpp;
	int		endian;
	int		line_len;
	void	*img_ptr;
	char	*pixel_ptr;
}	t_image;


typedef struct s_mlx_data
{
	int		flag;
	int 	ac;
	double 	x_mult;
	double 	y_mult;
	double 	y_cords;
	double 	x_cords;
	double	i;
	double	real;
	void	*win_ptr;
	void	*win_ptr2;
	void	*mlx_ptr;
	char	**av;
	t_image	img;
}	t_mlx_data;

int	Julia_set(t_mlx_data *data);
int	Mandelbrot(t_mlx_data *data);
int	fractol_formula(double z_real, double z_i, double c_real, double c_i);

#endif
