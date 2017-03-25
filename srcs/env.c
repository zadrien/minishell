/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 18:19:19 by zadrien           #+#    #+#             */
/*   Updated: 2017/03/17 19:53:22 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_env_cmd(t_env **env, char **tab, char **path)
{
	char	*cmd;
	char	**newenv;

	if ((newenv = sh_lvl(env, tab[0])) &&
		(cmd = ft_findbinary(path, tab[0])) != NULL)
	{
		time_4_magic(cmd, tab, newenv);
		reduc_shlvl(env, tab[0]);
		free(cmd);
	}
	else
		ft_errormsg("env: ", tab[0], ": No such file or directory.");
	ft_freetab(newenv);
}

void	printenv(t_env *env, char **tab, char **path)
{
	if (countab(tab) == 0)
		while (env)
		{
			if (env->var)
			{
				ft_putstr(env->var);
				ft_putchar('=');
				ft_putendl(env->value);
			}
			env = env->next;
		}
	else
		exec_env_cmd(&env, tab, path);
}

void	env(t_env **env, char **tab, char **path)
{
	int		i;
	int		j;

	i = 0;
	while (tab[i])
	{
		if ((j = test(tab[i])) == 1)
			i++;
		else
		{
			exec_env_cmd(env, tab + i, path);
			return ;
		}
	}
	printenv(*env, NULL, path);
	i = -1;
	while (tab[++i])
		ft_putendl(tab[i]);
}
