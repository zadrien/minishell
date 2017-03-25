/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 11:22:21 by zadrien           #+#    #+#             */
/*   Updated: 2017/03/17 19:54:10 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_env **env, char **tab)
{
	if (countab(tab) == 0)
		ft_putendl("");
	else
	{
		if (dollar(env, tab) == 1)
			ft_echo(env, tab);
	}
}

void	print_echo(char **tab, int index, char *s)
{
	if (tab[index + 1])
	{
		ft_putstr(s);
		ft_putchar(' ');
	}
	else
		ft_putendl(s);
}

char	*ft_stockbuff(char *str, char *buf)
{
	int		i;
	char	*tmp;

	if (str)
	{
		tmp = ft_strdup(str + 1);
		free(str);
	}
	i = ft_strlen(tmp);
	if (!(str = (char*)malloc(sizeof(char) * (i + ft_strlen(buf) + 1))))
		return (NULL);
	ft_bzero(str, ft_strlen(tmp) + ft_strlen(buf) + 1);
	str = ft_strcat(str, buf);
	str = ft_strcat(str, tmp);
	if (tmp)
		free(tmp);
	return (str);
}

void	ft_echo(t_env **env, char **tab)
{
	int		i;
	char	*s;
	t_env	*tmp;

	i = -1;
	while (tab[++i])
	{
		if (tab[i][0] == '$')
		{
			tmp = find_node(env, tab[i] + 1, NULL);
			s = ft_strdup(tmp->value);
		}
		else
			s = ft_strdup(tab[i]);
		print_echo(tab, i, s);
		free(s);
	}
}
