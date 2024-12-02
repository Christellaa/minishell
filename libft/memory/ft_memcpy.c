/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:15:13 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/25 09:38:05 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Copies n bytes from memory area src to memory area dest
** Memory areas must not overlap
** Returns a pointer to dest
*/

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*ptrdest;
	const char	*ptrsrc;
	size_t		i;

	if (!dest && !src)
		return (0);
	ptrdest = (char *)dest;
	ptrsrc = (const char *)src;
	i = 0;
	while (i < n)
	{
		ptrdest[i] = ptrsrc[i];
		i++;
	}
	return (dest);
}
/* 
#include <stdio.h>
#include <string.h> // For memset
#include <stddef.h> // For NULL
// Helper function to print test results
void print_test_result(int test_number, int passed) {
    printf("Test %d: %s\n", test_number, passed ? "Passed" : "Failed");
}
int main() {
    char dest[100];

    // Test 1: Copy nothing (n=0)
    memset(dest, 'A', 100);
    ft_memcpy(dest, "coucou", 0);
    int test1_passed = dest[0] == 'A';
    print_test_result(1, test1_passed);

    // Test 2: Copy a null pointer (src=NULL)
    char *rtn = (char *)ft_memcpy(dest, NULL, 0);
    int test2_passed = (rtn == dest && dest[0] == 'A');
    print_test_result(2, test2_passed);

    // Test 3: Copy zero bytes from source with non-zero n
    char src[] = {0, 0};
    ft_memcpy(dest, src, 2);
    int i = 0;
    while (i < 100 && dest[i] == 0) {
        i++;
    }
    int test3_passed = (i == 2 && dest[2] == 'A');
    print_test_result(3, test3_passed);

    // Test 4: Copy entire string (n large enough)
    memset(dest, 'A', 100);
    ft_memcpy(dest, "hello world", strlen("hello world"));
    int test4_passed = strncmp(dest, "hello world", strlen("hello world")) == 0;
    print_test_result(4, test4_passed);

    // Test 5: Copy part of a string (n less than string length)
    memset(dest, 'A', 100);
    ft_memcpy(dest, "hello world", 5);
    int test5_passed = strncmp(dest, "hello", 5) == 0;
    print_test_result(5, test5_passed);

    // Test 6: Copy to overlapping memory regions (dest after src)
    char overlapping_src[20] = "overlap";
    char overlapping_dest[20] = "original";
    ft_memcpy(overlapping_dest + 5, overlapping_src, strlen(overlapping_src));
    int test6_passed = strncmp(overlapping_dest, "origioverlap", \
                            strlen(overlapping_src) + 5) == 0;
    print_test_result(6, test6_passed);

    // Test 7: Copy to overlapping memory regions (dest before src)
    memset(overlapping_dest, 'A', 20);
    ft_memcpy(overlapping_dest, overlapping_dest + 5, 5);
    int test7_passed = strncmp(overlapping_dest, "AAAAAoverlap", \
                                strlen(overlapping_src) + 5) == 0;
    print_test_result(7, test6_passed);

    // Test 8: Copy from a null pointer (dest is valid)
    memset(dest, 'A', 100);
    ft_memcpy(dest, NULL, 5);
    int test8_passed = dest[0] == 'A'; // Check if original content remains
    print_test_result(8, test8_passed);

    int all_passed = test1_passed && test2_passed && test3_passed \
                                            && test4_passed &&
                      test5_passed && test6_passed && test7_passed \
                                            && test8_passed;
    if (all_passed) {
        printf("All tests passed!\n");
    } else {
        printf("Some tests failed.\n");
    }

    return 0;
}
 */
