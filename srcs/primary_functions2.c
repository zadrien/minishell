/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primary_functions2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 19:33:30 by zadrien           #+#    #+#             */
/*   Updated: 2017/03/17 19:36:33 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		verif_format(char **tab)
{
	int		i;

	i = -1;
	while (tab[++i])
		if (test(tab[i]) == 1)
			return (1);
	return (0);
}

int		ft_checkbin(DIR *dir, char *cmd)
{
	struct dirent *dirp;

	while ((dirp = readdir(dir)))
		if (ft_strcmp(dirp->d_name, cmd) == 0)
			return (1);
	return (0);
}

int		find_bin(char *path, char *file)
{
	DIR				*dir;
	struct dirent	*dirp;

	if ((dir = opendir(path)))
	{
		while ((dirp = readdir(dir)))
			if (ft_strcmp(dirp->d_name, file) == 0)
			{
				closedir(dir);
				return (1);
			}
		closedir(dir);
	}
	return (0);
}

int		seak(char *s)
{
	char *name;

	if (ft_strcmp(s, "minishell") == 0)
		return (1);
	else if ((name = ft_strrchr(s, '/')))
		if (ft_strcmp(name + 1, "minishell") == 0)
			return (1);
	return (0);
}

int		dollar(t_env **env, char **tab)
{
	int		i;
	t_env	*tmp;

	i = -1;
	while (tab[++i])
		if (tab[i][0] == '$')
			if (!(tmp = find_node(env, tab[i] + 1, NULL)))
			{
				ft_errormsg(tab[i] + 1, NULL, ": Undefined variable.");
				return (0);
			}
	return (1);
}
