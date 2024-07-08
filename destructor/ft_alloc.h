/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:37:51 by mzhukova          #+#    #+#             */
/*   Updated: 2024/07/08 14:42:24 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ALLOC_H
# define FT_ALLOC_H

# ifndef DEBUG
#  define DEBUG 0
# endif

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct t_allocs
{
	void			*ptr;
	struct t_allocs	*next;
}					t_allocs;

/* init */
bool				ft_alloc_init(void);

/* allocations */
void				*ft_calloc(size_t count, size_t size);
void				*ft_malloc(size_t size);

/* utils */
t_allocs			*ft_allocs(t_allocs *lst);

void				add_allocnode(t_allocs **lst, t_allocs *nnew);
t_allocs			*create_alloc(void *ptr);
int					ft_allocsize(void);

/* destructors */
void				ft_free(void *ptr);
void				ft_destructor(void);

#endif
