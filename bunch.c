#include <stdlib.h>

typedef void*	t_any64;
typedef unsigned char t_bool;

typedef struct	s_bunch
{
	void			**chunk;
	size_t			length;
	unsigned char	element_size;
	unsigned char	chunk_size_log2;
    unsigned char   depth;
}				t_bunch;

t_bunch			*ft_newbunch(unsigned char element_size, unsigned char chunk_size_log2);
void			ft_bunch(t_bunch *bunch, unsigned char element_size, unsigned char chunk_size_log2);
t_any64			*ft_put(t_bunch *bunch, t_any64 data);
void			*ft_get(t_bunch *bunch, size_t index);
void			ft_freebunch(t_bunch *bunch);
void			ft_clearbunch(t_bunch bunch);

void			ft_bunch(t_bunch *bunch, unsigned char element_size, unsigned char chunk_size_log2)
{
    bunch->element_size = element_size;
    bunch->chunk_size_log2 = chunk_size_log2;
    bunch->depth = 0;
    bunch->chunk = (void**)bunch;
}

t_bunch			*ft_newbunch(unsigned char element_size, unsigned char chunk_size_log2)
{
    t_bunch *ptr = malloc(sizeof(t_bunch));
    if (ptr)
        ft_bunch(ptr, element_size, chunk_size_log2);
    return ptr;
}

t_any64			*ft_put(t_bunch *bunch, t_any64 data)
{
    if ((bunch->length & ((1 << bunch->chunk_size_log2) - 1)) == 0)
    {
        if (bunch->length >= (1 << (bunch->depth * bunch->chunk_size_log2)))
        {
            void **last_chunk = bunch->chunk;
            size_t  ptrchunk_size = sizeof(void*) << bunch->chunk_size_log2;
            if(!(bunch->chunk = malloc(ptrchunk_size + (bunch->element_size << bunch->chunk_size_log2))))
                return 0;
            bunch->chunk[0] = last_chunk;
            bunch->chunk[1] = ((char*)bunch->chunk) + ptrchunk_size;
            bunch->depth++;
        }
        else
        {
            
        }
    }
    else bunch->last_addr++;
    *(bunch->last_addr) = data;
    return bunch->last_addr;
}

void		*ft_get(t_bunch *bunch, size_t index)
{
    void    **chunk = (void**)bunch;
    const size_t mask = (1 << bunch->chunk_size_log2) - 1;
    size_t depth = bunch->depth;
    while (--depth > 0)
        chunk = chunk[(index >> (depth << bunch->chunk_size_log2 - 1)) & mask];
    return (t_any64*)((long)chunk + (unsigned long)index & mask);
}
