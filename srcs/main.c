/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 16:45:02 by zadrien           #+#    #+#             */
/*   Updated: 2017/03/18 18:01:18 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include "../libft/libft.h"

char	**ft_getpath(t_env *env, char **path)
{
	char	**tab;

	if (path != NULL)
		ft_freetab(path);
	env = find_node(&env, "PATH", NULL);
	if (!env)
		return (NULL);
	tab = ft_strsplit(env->value, ':');
	return (tab);
}

void	tild(t_env *env, char **tab)
{
	int		i;
	t_env	*tmp;

	i = -1;
	tmp = find_node(&env, "HOME", NULL);
	while (tab[++i])
		if (tab[i][0] == '~')
			tab[i] = ft_stockbuff(tab[i], tmp->value);
}

char	**ft_output(t_env **env, char **path)
{
	int		i;
	char	*line;
	char	**tab;

	ft_putstr_fd("$> ", 2);
	if ((i = get_next_line(0, &line)) == 1)
	{
		tab = ft_split(line);
		if (tab != NULL)
			tild(*env, tab);
		ft_strdel(&line);
		return (tab);
	}
	else if (i == 0)
	{
		ft_putendl("exit");
		ft_strdel(&line);
		ft_exit(env, NULL, path);
	}
	return (NULL);
}

int		main(int ac, char **av, char **env)
{
	char	**tab;
	char	**path;
	t_env	*lstenv;

	if (ac != 1 && countab(av) != 1)
		ft_errormsg("usage: ", NULL, "./minishell");
	else
	{
		lstenv = init_env(env, &lstenv);
		path = ft_getpath(lstenv, NULL);
		while (42)
			if ((tab = ft_output(&lstenv, path)))
				if (countab(tab) >= 1)
				{
					init_cmd(&lstenv, tab, path);
					if (countab(tab) >= 2)
					{
						if (ft_strcmp(tab[1], "PATH") == 0)
							path = ft_getpath(lstenv, path);
					}
					ft_freetab(tab);
				}
	}
	return (0);
}
