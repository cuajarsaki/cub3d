/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 01:25:43 by rhonda            #+#    #+#             */
/*   Updated: 2025/05/05 02:01:59 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_args(t_game *game, char **argv)
{
    if (check_file_type(argv[1], CUB) == FAILURE)
		clean_exit(game, FAILURE);
	parse_game(game, argv[1]);
	return (0);
}
