# DSA-II Assignment 2: Sliding Window Technique
def max_sum_brute(a, k):
    if not 1 <= k <= len(a):
        raise ValueError("Part A requires 1 <= K <= n.")
    best = None
    for left in range(len(a) - k + 1):
        total = sum(a[left:left+k])
        best = total if best is None else max(best, total)
    return best

def max_sum_sliding(a, k):
    if not 1 <= k <= len(a):
        raise ValueError("Part A requires 1 <= K <= n.")
    window = sum(a[:k])
    best = window
    for right in range(k, len(a)):
        window += a[right] - a[right-k]
        best = max(best, window)
    return best

def validate_b(a, limit):
    if limit < 0:
        raise ValueError("Part B limit K must be non-negative.")
    if any(x < 0 for x in a):
        raise ValueError("Part B requires non-negative array values.")

def longest_brute(a, limit):
    validate_b(a, limit)
    best = (0, -1, -1)
    for left in range(len(a)):
        total = 0
        for right in range(left, len(a)):
            total += a[right]
            length = right-left+1
            if total <= limit and length > best[0]:
                best = (length, left, right)
    return best

def longest_sliding(a, limit):
    validate_b(a, limit)
    left = 0
    total = 0
    best = (0, -1, -1)
    for right, value in enumerate(a):
        total += value
        while total > limit and left <= right:
            total -= a[left]
            left += 1
        length = right-left+1
        if length > best[0]:
            best = (length, left, right)
    return best

def show_a(a, k):
    print(f"Array: {a}, K={k} | brute={max_sum_brute(a,k)} | sliding={max_sum_sliding(a,k)}")
def show_b(a, limit):
    print(f"Array: {a}, limit={limit} | brute={longest_brute(a,limit)} | sliding={longest_sliding(a,limit)}")

if __name__ == "__main__":
    print("DSA-II Assignment 2: Sliding Window Technique\n\nPART A: Maximum sum of K consecutive elements")
    show_a([2,1,5,1,3,2],3)
    show_a([-4,-2,-7],2)
    show_a([6],1)
    show_a([1,2,3],3)
    print("\nPART B: Longest subarray with sum at most K (0-based indices)")
    show_b([1,2,1,1,3],4)
    show_b([5,1,1],2)
    show_b([4,2,1],0)
    show_b([0,0,1,0],1)
