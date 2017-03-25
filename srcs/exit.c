/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 17:45:59 by zadrien           #+#    #+#             */
/*   Updated: 2017/03/16 20:12:57 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_env **lst, char **tab, char **path)
{
	t_env	*tmp;
	int		i;

	i = 0;
	if ((i = countab(tab)) > 1)
		return (ft_errormsg("exit: ", NULL, "Too many arguments."));
	else if (i == 1)
		i = ft_atoi(tab[0]);
	while ((*lst))
	{
		tmp = *lst;
		*lst = (*lst)->next;
		freenode(tmp);
	}
	ft_freetab(path);
	exit(i);
}
