/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:55:39 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/09 11:03:36 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//Return 1 if the character is a valid map character
int	is_in_mapset(char c)
{
	if (c == '1' || c == '0')
		return (TRUE);
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (TRUE);
	return (FALSE);
}

int	is_in_playerset(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (TRUE);
	return (FALSE);
}

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (TRUE);
	return (FALSE);
}

void	free_array(char **arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (ft_isspace(line[i]) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
