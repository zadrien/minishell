/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 09:30:33 by zadrien           #+#    #+#             */
/*   Updated: 2017/03/25 15:57:54 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_access(char *s)
{
	if (access(s, F_OK) == -1)
		ft_errormsg(NULL, s, ": No such file or directory");
	else if (access(s, R_OK) == -1)
		ft_errormsg(NULL, s, ": Permission denied.");
	else
		ft_errormsg(NULL, s, ": Not a directory.");
}

void	init_pwd(t_env **env)
{
	t_env	*tmp;
	t_env	*npwd;
	char	*p;
	char	buf[PATH_MAX];

	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	if (!(npwd = (t_env*)malloc(sizeof(t_env))))
		return ;
	p = ft_strdup(getcwd(buf, PATH_MAX));
	npwd->var = ft_strdup("PWD");
	npwd->value = ft_strdup(p);
	npwd->next = NULL;
	free(p);
	tmp->next = npwd;
}

void	cd_home(t_env **env)
{
	t_env	*tmp;
	char	*home;
	char	*oldpwd;

	oldpwd = NULL;
	if (!(tmp = find_node(env, "HOME", NULL)))
		ft_errormsg("minishell: cd: ", NULL, "HOME not set");
	else
	{
		home = ft_strdup(tmp->value);
		if ((tmp = find_node(env, "PWD", NULL)))
			oldpwd = ft_strdup(tmp->value);
		met_hode(env, home);
		old_pwd(env, oldpwd);
		ft_strdel(&home);
		ft_strdel(&oldpwd);
	}
}

void	change_directory(t_env **env, char **tab)
{
	t_env	*tmp;
	char	*oldpwd;
	char	buf[1024];

	if (chdir(tab[0]) == -1)
		ft_access(tab[0]);
	else
	{
		if ((tmp = find_node(env, "PWD", NULL)))
		{
			oldpwd = ft_strdup(tmp->value);
			addvalue(&tmp, getcwd(buf, 1024));
			old_pwd(env, oldpwd);
			ft_strdel(&oldpwd);
		}
		else
			init_pwd(env);
	}
}

void	ft_cd(char **tab, t_env **env)
{
	if (countab(tab) == 0)
		cd_home(env);
	else if (countab(tab) > 1)
		ft_errormsg(NULL, NULL, "cd: Too many arguments.");
	else if (ft_strcmp(tab[0], "-") == 0)
		go_oldpwd(env);
	else
		change_directory(env, tab);
}
