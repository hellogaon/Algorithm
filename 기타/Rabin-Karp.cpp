// Rabin-Karp Algorithm
// 문자열 S의 길이 M, S[i:i+M-1]의 해쉬값을 H[i]라 할 때,
// H[i] = S[i] * 2^(M-1) + S[i+1] * 2^(M-2) ... S[i+M-1] * 2^0
// H[i+1] = (H[i] - S[i] * 2^(M-1)) * 2 + S[i+M]
// 다음 항 H[i+1]을 바로 구할 수 있다!