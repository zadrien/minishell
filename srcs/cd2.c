/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 13:49:13 by zadrien           #+#    #+#             */
/*   Updated: 2017/03/17 19:29:08 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	old_pwd(t_env **env, char *s)
{
	t_env *tmp;
	t_env *node;

	if (s)
	{
		if (!(tmp = find_node(env, "OLDPWD", NULL)))
		{
			tmp = *env;
			while (tmp->next)
				tmp = tmp->next;
			if (!(node = (t_env *)malloc(sizeof(t_env))))
				return ;
			node->next = NULL;
			init_cpy(&node, "OLDPWD", s);
			tmp->next = node;
		}
		else
			addvalue(&tmp, s);
	}
}

void	met_hode(t_env **env, char *home)
{
	t_env	*tmp;
	char	buf[PATH_MAX];

	if (chdir(home) == -1)
		ft_access(home);
	else
	{
		tmp = find_node(env, "PWD", NULL);
		if (tmp)
			addvalue(&tmp, getcwd(buf, PATH_MAX));
		else
			init_pwd(env);
	}
}

void	go_oldpwd(t_env **env)
{
	t_env	*tmp;
	char	*oldpwd;
	char	*pwd;

	if (!(tmp = find_node(env, "PWD", NULL)))
		return (ft_errormsg("minishell: ", NULL, "cd: PWD not set"));
	oldpwd = ft_strdup(tmp->value);
	if (!(tmp = find_node(env, "OLDPWD", NULL)))
		ft_errormsg("minishell: ", NULL, "cd: OLDPWD not set");
	else
	{
		pwd = ft_strdup(tmp->value);
		if (chdir(tmp->value) == -1)
			ft_access(tmp->value);
		else
		{
			addvalue(&tmp, oldpwd);
			tmp = find_node(env, "PWD", NULL);
			addvalue(&tmp, pwd);
			free(pwd);
		}
	}
	free(oldpwd);
}
