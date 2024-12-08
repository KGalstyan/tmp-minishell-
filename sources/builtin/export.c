/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:32:07 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/07 16:01:58 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_env_export *export)
{
	t_env_export	*temp;

	temp = export;
	while (temp)
	{
		if (temp->key)
			printf("declare -x %s", temp->key);
		if (temp->value)
			printf("=\"%s\"\n", temp->value);
		else
			printf("\n");
		temp = temp->next;
	}
}

t_env_export	*add_oldpwd(t_env_export *env)
{
	t_env_export	*oldpwd;
	t_env_export	*temp;

	oldpwd = NULL;
	temp = env;
	while (temp && ft_strcmp(temp->key, "OLDPWD") != 0)
		temp = temp->next;
	if (!temp)
	{
		oldpwd = (t_env_export *)malloc(sizeof(t_env_export));
		if (!oldpwd)
			return (NULL);
		oldpwd->key = ft_strdup("OLDPWD");
		oldpwd->value = NULL;
		oldpwd->next = env;
		return (oldpwd);
	}
	else
		return (env);
}

// t_env_export *add_oldpwd(t_data *data)
// {
//     t_env_export *oldpwd = NULL;
//     t_env_export *temp;

//     temp = data->export;
//     while(temp && ft_strcmp(temp->key, "OLDPWD") != 0)
//         temp = temp->next;
//     if(!temp)
//     {
//         oldpwd = (t_env_export *)malloc(sizeof(t_env_export));
//         if(!oldpwd)
//             return(NULL);
//         oldpwd->key = ft_strdup("OLDPWD");
//         oldpwd->value = NULL;
//         oldpwd->next = data->export;
//         return (oldpwd);
//     }
//     else
//         return (data->export);
// }

// int add_node(t_env_export **export, char *key, char *value)
// {
//     t_env_export *node;

//     if (!key || !export || !*export)
//         return (EXIT_FAILURE);
//     node = (t_env_export *)malloc(sizeof(t_env_export));
//     if(!node)
//         return (EXIT_FAILURE);
//     node->key = ft_strdup(key);
//     if(value)
//         node->value = ft_strdup(value);
//     else
//         node->value = NULL;
//     node->next = *export;
//     *export = node;
//     // free_env_node(node);
//     return (EXIT_SUCCESS);
// }

t_env_export	*add_node(t_env_export *export, char *key, char *value)
{
	t_env_export	*node;

	if (update_env(export, key, value) == EXIT_SUCCESS)
		return (export);
	if (!key || !export)
		return (NULL);
	node = (t_env_export *)malloc(sizeof(t_env_export));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->next = export;
	export = node;
	return (export);
}

t_env_export	*set_variable(t_env_export *export, char *var)
{
	t_env_export	*new;
	char			*key;
	char			*value;

	if (ft_strchr(var, '=') == 0)
	{
		new = add_node(export, var, NULL);
		return (new);
	}
	key = find_key(var);
	value = find_value(var);
	new = add_node(export, key, value);
	free(key);
	free(value);
	return (new);
}

// t_env_export *export(t_env_export *export, char **args)
// {
//     int i;

//     if(!export || !args)
//         return(NULL);
//     if(args[0] && !args[1])
//         return (print_export(export), export);
//     i = 1;
//     while(args[i])
//     {
//         if(check_variable_name(args[i]) == EXIT_SUCCESS)
//         {
//             export = set_variable(export, args[i]);
//             if(!export)
//                 return (NULL);
//             // if(set_variable(export, args[i]) != EXIT_SUCCESS)
//             //     return (EXIT_FAILURE);
//         }
//         else
//             minishell_error("export", args[i], "not a valid identifier");
//         i++;
//     }
//     return (export);
// }

int	export(t_data *data, char **args)
{
	int	i;
	int	status;

	status = 0;
	if (!data->export || !args)
		return (EXIT_FAILURE);
	if (args[0] && !args[1])
		return (print_export(data->export), EXIT_SUCCESS);
	i = 1;
	while (args[i])
	{
		if (check_variable_name(args[i]) == EXIT_SUCCESS)
		{
			data->export = merge(set_variable(data->export, args[i]),
					ft_strcmp);
			data->env = set_variable(data->env, args[i]);
		}
		else
		{
			status = 1;
			minishell_error("export", args[i], "not a valid identifier");
		}
		i++;
	}
	return (status);
}

// int export(t_env_export *export, char **args)
// {
//     int i;

//     if(!export || !args)
//         return(EXIT_FAILURE);
//     if(args[0] && !args[1])
//         return (print_export(export), EXIT_SUCCESS);
//     i = 1;
//     while(args[i])
//     {
//         if(check_variable_name(args[i]) == EXIT_SUCCESS)
//         {
//             export = set_variable(export, args[i]);
//             if(!export)
//                 return (EXIT_FAILURE);
//             if(set_variable(export, args[i]) != EXIT_SUCCESS)
//                 return (EXIT_FAILURE);
//         }
//         else
//             minishell_error("export", args[i], "not a valid identifier");
//         i++;
//     }
//     return (EXIT_SUCCESS);
// }
