/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_finder2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:02:53 by zadrien           #+#    #+#             */
/*   Updated: 2017/03/30 13:18:00 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		isexec(char *path)
{
	struct stat buf;

	if (lstat(path, &buf) == -1)
		return (0);
	if ((buf.st_mode & S_IXUSR))
		return (1);
	return (0);
}

char	*path_1case(char *cmd)
{
	int		i;
	int		index;
	char	*ncmd;

	i = -1;
	while (cmd[++i])
		if (cmd[i] == '/')
			index = i;
	i = -1;
	if (!(ncmd = ft_strnew(index + 1)))
		return (NULL);
	while (++i <= index)
		ncmd[i] = cmd[i];
	return (ncmd);
}

void	exec_1case(t_env **env, char **tab)
{
	char	*npath;
	char	**newenv;

	if (!(npath = path_1case(tab[0])))
		return ;
	if (find_bin(npath, (ft_strrchr(tab[0], '/') + 1), tab[0]) == 1)
	{
		newenv = sh_lvl(env, tab[0]);
		time_4_magic(NULL, tab, newenv);
		reduc_shlvl(env, tab[0]);
		ft_freetab(newenv);
	}
	else
		ft_errormsg("minishell: ", tab[0], ": Command not found.");
	ft_strdel(&npath);
}

void	binary_finder(t_env **env, char **cmd, char **path)
{
	if (ft_strncmp(cmd[0], "./", 2) == 0)
		exec_1case(env, cmd);
	else
		exec_cmd(cmd, path, env);
}
