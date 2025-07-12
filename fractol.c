/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42lisba.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:17:36 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/21 13:43:49 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "sys/time.h"

// new frame
void	key_hook_aux(int k, t_mlx_data *data)
{
	if (k == XK_Down && data->flag != 2)
		go_up(data, 10);
	if (k == XK_Up && data->flag != 2)
		go_down(data, 10);
	if (k == XK_Right && data->flag != 2)
		go_left(data, 10);
	if (k == XK_Left && data->flag != 2)
		go_right(data, 10);
	if (k == XK_Up && data->flag == 2)
		burning_ship_go(data, 2);
	if (k == XK_Down && data->flag == 2)
		burning_ship_go(data, 3);
	if (k == XK_Left && data->flag == 2)
		burning_ship_go(data, 0);
	if (k == XK_Right && data->flag == 2)
		burning_ship_go(data, 1);
	if (k == XK_KP_Add)
		zoom(data, 1);
	if (k == XK_KP_Subtract)
		zoom(data, -1);
}

int	key_hook(int key, t_mlx_data *data)
{
	struct timeval start;
	struct timeval end;
	gettimeofday(&start, NULL);
	if (key == XK_Escape)
		exit_func(data);
	/* if (key == XK_space && ft_strncmp(data->av[1], "Julia", 6))
		restart_data(data, data->av, 1); */
	if (key == XK_space && ft_strncmp(data->av[1], "Julia", 6))
		j_m_bs(data);
	key_hook_aux(key, data);
	if (key > XK_0 && key <= XK_7)
		color_code(key, data);
	if (key == XK_KP_Multiply)
	{
		data->sc += 50;
		j_m_bs(data);
	}
	if (key == XK_KP_Divide && data->sc > 50)
	{
		data->sc -= 50;
		j_m_bs(data);
	}
	gettimeofday(&end, NULL);
	printf("Demorou %ld ms a dar load a imagem\n", (1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)) / 1000);
	fflush(stdout);
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->img.img_ptr, 0, 0);
	return (0);
}

/* void	mouse_hook_aux(int key, int x, int y, t_mlx_data *data)
{
	if (key == 3 && data->flag == 0 && data->win_ptr2)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr2);
		data->win_ptr2 = NULL;
		data_set(data, data->lr, data->li);
		julia_set(data);
	}
	if (key == 4)
		mouse_zoom(data, x, y, -1);
	if (key == 5)
		mouse_zoom(data, x, y, 1);
}*/ 

/*int	mouse_hook(int key, int x, int y, t_mlx_data *data)
{
	float	rx;
	float	ry;

	rx = x;
	ry = y;
	if (key == 1 && data->flag == 0)
	{
		if (data->win_ptr2 == NULL)
			data->win_ptr2 = \
				mlx_new_window(data->mlx_ptr, WIDTH, HIGHT, "julia_set");
		data->lr = ((rx * data->x_mult / WIDTH) - data->x_cords);
		data->li = data->y_cords - ((ry * data->y_mult) / HIGHT);
		second_julia_set(data,
			((rx * data->x_mult / WIDTH) - data->x_cords) \
			, data->y_cords - ((ry * data->y_mult) / HIGHT));
	}
	if (key == 2)
		j_m_bs(data);
	if (key == 2 && !check_color(&data->img, rx, ry) && data->x_mult == 2.65)
		draw_orbit(data, (((rx) * data->x_mult / WIDTH) - data->x_cords) \
			, data->y_cords - ((ry * data->y_mult) / HIGHT));
	mouse_hook_aux(key, x, y, data);
	return (0);
}*/

int	main(int ac, char **av)
{
	t_mlx_data	data;

	parse(ac, av);
	restart_data(&data, av, 0);
	init_fractol(&data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, key_hook, &data);
	// mlx_hook(data.win_ptr, ButtonPress, ButtonPressMask, mouse_hook, &data);
	struct timeval start;
	struct timeval end;
	gettimeofday(&start, NULL);
	j_m_bs(&data);
	gettimeofday(&end, NULL);
	printf("Demorou %ld ms a dar load a imagem\n", (1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)) / 1000);
	fflush(stdout);
	mlx_hook(data.win_ptr, 17, 0l, exit_func, &data);
	mlx_loop(data.mlx_ptr);
}
