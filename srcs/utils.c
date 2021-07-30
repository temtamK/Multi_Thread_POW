#include "block.h"

size_t	ft_strlen(const unsigned char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}


size_t	ft_strlcpy(char *dest, const unsigned char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	if (!dest || !src)
		return (0);
	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (size == 0)
		return (src_len);
	i = 0;
	while (src[i] != '\0' && i < (size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}

char	*ft_substr(unsigned char const *s, unsigned int start, size_t len)
{
	char			*new;
	unsigned int	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (calloc(1, sizeof(char)));
	if (!(new = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	ft_strlcpy(new, s + start, len + 1);
	return (new);
}

size_t		num_count_base(unsigned long long int n, char *base)
{
	size_t					len;
	unsigned long long int	base_len;

	len = 1;
	base_len = strlen(base);
	while (n >= base_len)
	{
		n = n / base_len;
		len++;
	}
	return (len);
}

BYTE		*ft_itoa_base(unsigned long long int n, char *base)
{
	BYTE		*str;
	int			num_len;
	int			base_len;

	num_len = num_count_base(n, base);
	base_len = strlen(base);
	if (!(str = calloc((num_len + 1), sizeof(BYTE))))
		return (NULL);
	str[num_len] = '\0';
	while (num_len)
	{
		str[--num_len] = base[n % base_len];
		n = n / base_len;
	}
	return (str);
}

uint32_t	ft_strtoui(BYTE *hash)
{
	char div[4];
	uint32_t ret;
	int i;

	i = 0;
	while (i < 3)
	{
		div[i] = hash[i];
		i++;
	}
	ret = strtoul(div, NULL, 16);
	return (ret);
}
