/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:45:49 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/17 12:33:23 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# ifndef HIGHT
#  define HIGHT 1000
# endif
# ifndef WIDTH
#  define WIDTH 1060
# endif

# include "mlx_linux/mlx_int.h"
# include "mlx_linux/mlx.h"
# include <math.h>

typedef struct s_comp
{
	double	real;
	double	i;
	double	c_r;
	double	c_i;
	double	z_r;
	double	z_i;
	double	r_min;
	double	r_max;
	double	i_min;
	double	i_max;

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
	int		col;
	int		flag;
	int		ac;
	int		sc;
	double	a;
	double	b;
	double	c;
	double	d;
	double	x_mult;
	double	y_mult;
	double	y_cords;
	double	x_cords;
	double	i;
	double	real;
	void	*win_ptr;
	void	*win_ptr2;
	void	*mlx_ptr;
	char	**av;
	double	lr;
	double	li;
	t_image	img;
	t_image	img2;
	t_comp	n;
}	t_mlx_data;

int		julia_set(t_mlx_data *data);
int		Mandelbrot(t_mlx_data *data);
int		fractol_formula(t_mlx_data *data);
void	draw_orbit(t_mlx_data *data, float c_real, float c_i);
int		check_color(t_image *img, float x, float y);
void	go_up(t_mlx_data *data, int divide);
void	go_down(t_mlx_data *data, int divide);
void	go_left(t_mlx_data *data, int divide);
void	go_right(t_mlx_data *data, int divide);
void	my_put_pixel(t_image *img, int x, int y, int color);
void	my_cpy_pixel_vert(t_image *img, int x, int y, int color);
void	my_cpy_pixel_hori(t_image *img, int x, int y, int color);
void	data_set(t_mlx_data *data, float rx, float ry);
void	init_fractol(t_mlx_data *data);
void	zoom(t_mlx_data *data, int flag);
int		fractol_formula(t_mlx_data *data);
int		julia_set(t_mlx_data *data);
int		mandelbrot(t_mlx_data *data);
int		second_julia_set(t_mlx_data *data, float r, float i);
void	julia_or_mandelbrot(t_mlx_data *data);
void	mouse_zoom(t_mlx_data *data, int x, int y, int flag);
void	restart_data(t_mlx_data *data, int ac, char **av);
int		exit_func(t_mlx_data *data);
int		go_func(t_mlx_data *data, double x, double y);
void	key_hook_aux(int key, t_mlx_data *data);
void	color_code(int key, t_mlx_data *data);

#endif
