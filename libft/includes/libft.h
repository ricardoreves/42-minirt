/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:21:49 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/01/30 18:20:59 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

typedef unsigned int	t_uint;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_node
{
	struct s_node	*prev;
	struct s_node	*next;
	void			*content;
}	t_node;

typedef struct s_dlist
{
	size_t	length;
	t_node	*first;
	t_node	*last;
}	t_dlist;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isascii(int c);
int		ft_isalnum(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_isnumber(char *s);
int		ft_ischarset(int c, const char *set);

int		ft_toupper(int c);
int		ft_tolower(int c);

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strncpy(char *dst, char *src, size_t size);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strcat(char *dst, const char *src);
char	*ft_strncat(char *dst, const char *src, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);

int		ft_atoi(const char *str);
long	ft_atol(const char *str);
t_uint	ft_atoi_base(const char *str, const char *base);
t_uint	ft_hextoi(const char *str);
int		ft_ilen(int n);

void	ft_swap(int *a, int *b);
void	ft_quicksort(int i_tab[], int size);
void	ft_bubsort(int i_tab[], int n);

void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	ft_memdel(void **pt);

void	*ft_calloc(size_t count, size_t size);
void	*ft_realloc(void *pt, size_t size);

char	*ft_strdup(const char *src);
char	*ft_strldup(char *src, size_t l);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strljoin(char *s1, char *s2, size_t l);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_itoa(int n);
char	*ft_uitoa(unsigned int n);
char	*ft_ultoa(unsigned long n);
char	*ft_itoa_base(int n, char *base);
char	*ft_uitoa_base(unsigned int n, char *base);
char	*ft_ultoa_base(unsigned long n, char *base);
char	**ft_split(const char *s, char c);
char	**ft_splitset(char *str, char *charset);
void	ft_clearsplit(char **split);
size_t	ft_count_words(const char *s, char c);
int		ft_count_wordset(char *str, char *charset);

void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void	ft_putchar_fd(char c, int fd);
void	ft_putchar(char c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putstr(char *s);
void	ft_putendl_fd(char *s, int fd);
void	ft_putendl(char *s);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr(int n);
void	ft_putnbr_base(int n, char *base);

int		ft_printf(const char *format, ...);
char	*get_next_line(int fd);

t_list	*ft_lstnew(void *content);
t_list	*ft_lstprelast(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
int		ft_lstsize(t_list *lst);
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	*ft_getnblist(t_list *lst, int nb);

t_dlist	*ft_dlnew(void);
void	ft_dlinit(t_dlist *dl);
t_dlist	*ft_dlcpy(t_dlist *dl, void *(*f)(void *));
t_dlist	*ft_dladdfirst(t_dlist *dl, void *content);
t_dlist	*ft_dladdlast(t_dlist *dl, void *content);
t_node	*ft_dlpushfirst(t_dlist *dl);
t_node	*ft_dlpushlast(t_dlist *dl);
t_dlist	*ft_dlputfirst(t_dlist *dl, t_node *node);
t_dlist	*ft_dlputlast(t_dlist *dl, t_node *node);
int		ft_dlisordered(t_dlist *dl, int (*f)(t_node *, t_node *));
void	*ft_dlgetcontent(t_dlist *dl, size_t i);
void	ft_dlclear(t_dlist **dl, void (*f)(void *));
void	ft_printdlsti(t_dlist *dl, int rev, int (*f)(t_node *, t_node *));

int		ft_sqrt(int n);
int		ft_abs(int i);

void	ft_print_int_array(int arr[], int size);

#endif
