def min_operations_to_one(n):
    dp = [0] * (n + 1)  # dp[i]: i를 1로 만들기 위한 최소 연산 수

    for i in range(2, n + 1):
        # 1을 빼는 연산을 기본으로
        dp[i] = dp[i - 1] + 1
        
        # 2로 나누어 떨어지면 비교해서 최소 선택
        if i % 2 == 0:
            dp[i] = min(dp[i], dp[i // 2] + 1)
        
        # 3으로 나누어 떨어지면 비교해서 최소 선택
        if i % 3 == 0:
            dp[i] = min(dp[i], dp[i // 3] + 1)

    return dp[n]

# 예시 실행
n = int(input())
print(min_operations_to_one(n))