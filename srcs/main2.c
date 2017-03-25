/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:13:13 by zadrien           #+#    #+#             */
/*   Updated: 2017/03/25 15:58:30 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freetab(char **tab)
{
	int		i;

	i = -1;
	if (!tab)
		return ;
	while (tab[++i])
		ft_strdel(&tab[i]);
	free(tab);
}

int		countab(char **tab)
{
	int		i;

	i = 0;
	if (tab)
		while (tab[i])
			i++;
	return (i);
}

void	time_4_magic(char *cmd, char **tab, char **env)
{
	pid_t	son;

	son = fork();
	if (son == 0)
	{
		if (cmd)
			execve(cmd, tab, env);
		else
			execve(tab[0], tab, env);
	}
	else
		wait(NULL);
}

void	exec_cmd(char **tab, char **path, t_env **env)
{
	char	*cmd;
	char	**newenv;

	if (find_path(*env) == 0)
		ft_errormsg("minishell: ", tab[0], " PATH not set");
	else
	{
		if ((newenv = sh_lvl(env, tab[0])) &&
			(cmd = ft_findbinary(path, tab[0])))
		{
			time_4_magic(cmd, tab, newenv);
			reduc_shlvl(env, tab[0]);
			ft_strdel(&cmd);
		}
		else
			ft_errormsg("minishell: ", tab[0], ": command not found");
		ft_freetab(newenv);
	}
}

void	init_cmd(t_env **lst, char **tab, char **path)
{
	if (ft_strcmp(tab[0], "env") == 0)
		env(lst, tab + 1, path);
	else if (ft_strcmp(tab[0], "echo") == 0)
		echo(lst, tab + 1);
	else if (ft_strcmp(tab[0], "exit") == 0)
		ft_exit(lst, tab + 1, path);
	else if (ft_strcmp(tab[0], "unsetenv") == 0)
		ft_unsetenv(lst, tab + 1);
	else if (ft_strcmp(tab[0], "setenv") == 0)
		ft_setenv(lst, tab + 1, path);
	else if (ft_strcmp(tab[0], "cd") == 0)
		ft_cd(tab + 1, lst);
	else
		binary_finder(lst, tab, path);
}
