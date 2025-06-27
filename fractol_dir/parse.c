/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42lisba.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:57:21 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/21 13:50:50 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	print_loc(void)
{
	write(2, "You can use:\n\t'Mandelbrot' to print a Mandelbrot set.\n", 55);
	write(2, "\t'Burning_ship' to print a Burning_ship set.\n", 45);
	write(2, "\t'Julia' and the cordinates of the complex number", 50);
	write(2, " (without letters) to print a Julia set\n", 41);
	exit (1);
}

void	print_nbr_semantic(char *av)
{
	write (2, "Wrong number semantic, bad use of '", 36);
	write (2, av, 1);
	write (2, "'.\n", 4);
	exit(1);
}

void	check_semantic(char *av)
{
	int	ind;

	ind = 0;
	while ((av[ind] >= 9 && av[ind] <= 13) || av[ind] == 32)
		ind++;
	if (av[ind] == '\0')
		write (2, "no number found.\n", 18);
	if (av[ind] == '\0')
		exit(1);
	if (av[ind] == '\0')
		print_nbr_semantic(av + ind);
	if ((av[ind] == '+' || av[ind] == '-'))
		ind++;
	if (av[ind] < '0' && av[ind] > '9')
		print_nbr_semantic(av + ind);
	while (av[ind] >= '0' && av[ind] <= '9')
		ind++;
	if (av[ind] == '.' || av[ind] == ',')
		ind++;
	while (av[ind] >= '0' && av[ind] <= '9')
		ind++;
	if (av[ind] != '\0')
		print_nbr_semantic(av + ind);
}

void	parse(int ac, char **av)
{
	if (ac == 1 || ac == 3 || ac > 4)
		print_loc();
	if (ac == 2 && (strncmp(av[1], "Mandelbrot", 11) == 0 \
		|| strncmp(av[1], "Burning_ship", 11) == 0))
		return ;
	else if (ac == 2)
		print_loc();
	if (ac == 4 && strncmp(av[1], "Julia", 10))
		print_loc();
	while (--ac > 1)
		check_semantic(av[ac]);
}

int	close_window(void *data)
{
	exit_func(data);
	return (0);
}
