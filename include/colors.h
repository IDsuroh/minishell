/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:56:52 by suroh             #+#    #+#             */
/*   Updated: 2025/01/15 21:38:03 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

#define RESET  "\033[0m"          // Reset to default color
#define ID     "\033[38;5;32m"    // Green for identifiers
#define LSS    "\033[38;5;33m"    // Light blue for '<'
#define GRT    "\033[38;5;34m"    // Cyan for '>'
#define DLSS   "\033[38;5;36m"    // Light cyan for '<<'
#define DGRT   "\033[38;5;93m"    // Bright pink for '>>'
#define PP     "\033[38;5;94m"    // Bright purple for '|'
#define ND     "\033[38;5;196m"   // Red for '&&'
#define OR     "\033[38;5;202m"   // Orange for '||'
#define VR     "\033[38;5;226m"   // Yellow for variables
#define XVR    "\033[38;5;229m"   // Light yellow for special variables ($?)
#define PD     "\033[38;5;45m"    // Blue for $$ (process ID)


#endif
