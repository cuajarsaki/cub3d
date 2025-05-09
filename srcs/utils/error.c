/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 00:14:23 by rhonda            #+#    #+#             */
/*   Updated: 2025/05/05 02:09:46 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int err_msg(char *detail, char *msg, int code)
{
    ft_putstr_fd("cub3D: Error", 2);
    if (detail)
    {
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(detail, 2);
    }
    if (msg)
    {
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(msg, 2);
    }
    ft_putstr_fd("\n", 2);
    return (code);
}
