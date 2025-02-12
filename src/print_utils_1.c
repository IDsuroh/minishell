/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:39:50 by suroh             #+#    #+#             */
/*   Updated: 2025/02/08 18:50:44 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/colors.h"

const char	*token_type_to_string(t_token_type type)
{
	if (type == T_NONE)
		return ("T_NONE");
	else if (type == T_IDENTIFIER)
		return ("T_IDENTIFIER");
	else if (type == T_LESS)
		return ("T_LESS");
	else if (type == T_GREAT)
		return ("T_GREAT");
	else if (type == T_DLESS)
		return ("T_DLESS");
	else if (type == T_DGREAT)
		return ("T_DGREAT");
	else if (type == T_PIPE)
		return ("T_PIPE");
	else if (type == T_AND)
		return ("T_AND");
	else if (type == T_OR)
		return ("T_OR");
	else if (type == T_VAR)
		return ("T_VAR");
	else if (type == T_XVAR)
		return ("T_XVAR");
	else if (type == T_PID)
		return ("T_PID");
	return ("UNKNOWN");
}

const char	*get_token_color(t_token_type type)
{
	if (type == T_NONE)
		return (RESET);
	else if (type == T_IDENTIFIER)
		return (ID);
	else if (type == T_LESS)
		return (LSS);
	else if (type == T_GREAT)
		return (GRT);
	else if (type == T_DLESS)
		return (DLSS);
	else if (type == T_DGREAT)
		return (DGRT);
	else if (type == T_PIPE)
		return (PP);
	else if (type == T_AND)
		return (ND);
	else if (type == T_OR)
		return (OR);
	else if (type == T_VAR)
		return (VR);
	else if (type == T_XVAR)
		return (XVR);
	else if (type == T_PID)
		return (PD);
	return (RESET);
}
