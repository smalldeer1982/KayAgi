# Hidden Permutations

## 题目描述

This is an interactive problem.

The jury has a permutation $ p $ of length $ n $ and wants you to guess it. For this, the jury created another permutation $ q $ of length $ n $ . Initially, $ q $ is an identity permutation ( $ q_i = i $ for all $ i $ ).

You can ask queries to get $ q_i $ for any $ i $ you want. After each query, the jury will change $ q $ in the following way:

- At first, the jury will create a new permutation $ q' $ of length $ n $ such that $ q'_i = q_{p_i} $ for all $ i $ .
- Then the jury will replace permutation $ q $ with pemutation $ q' $ .

You can make no more than $ 2n $ queries in order to quess $ p $ .

## 说明/提示

In the first test case the hidden permutation $ p = [4, 2, 1, 3] $ .

Before the first query $ q = [1, 2, 3, 4] $ so answer for the query will be $ q_3 = 3 $ .

Before the second query $ q = [4, 2, 1, 3] $ so answer for the query will be $ q_2 = 2 $ .

Before the third query $ q = [3, 2, 4, 1] $ so answer for the query will be $ q_4 = 1 $ .

In the second test case the hidden permutation $ p = [1, 3, 4, 2] $ .

Empty strings are given only for better readability. There will be no empty lines in the testing system.

## 样例 #1

### 输入

```
2
4

3

2

1

4

2

4

4```

### 输出

```
? 3

? 2

? 4

! 4 2 1 3

? 2

? 3

? 2

! 1 3 4 2```

# 题解

## 作者：XL4453 (赞：2)

### $\text{Difficulty : 1700}$

---
### 解题思路：

本质上是不断进行一个固定的置换。

考虑对于一个位置连续询问两次，如果第一次得到的答案为 $a$，而第二次得到的答案为 $b$，根据题目给出的操作有：$p_a=b$。为了节约询问次数，不妨一直盯着一个位置一直询问直到出现之前出现过的，直接清除一个环。

最坏情况是 $p_i=i$，这样每一个位置都需要询问两次，总次数为 $2n$，恰好卡到上限，注意不要有多余操作。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
int T,ans[10005],rec[10005],cnt,n;
void ask(int x,int y){
	printf("? %d\n",x);
	fflush(stdout);
	scanf("%d",&rec[y]);
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)ans[i]=0;
		for(int i=1;i<=n;i++){
			if(ans[i]!=0)continue;
			ask(i,1);ask(i,2);cnt=2;
			while(rec[cnt]!=rec[1])ask(i,++cnt);
			for(int i=1;i<cnt;i++)ans[rec[i]]=rec[i+1];
		}
		printf("! ");
		for(int i=1;i<=n;i++)
		printf("%d ",ans[i]);
		printf("\n");
		fflush(stdout);
	}
	return 0;
}
```


---

## 作者：清烛 (赞：2)

## Description
交互题，猜一个排列 $p$（$n\le 10000$）。初始有一个排列 $q_i = i$，每次可以询问一个 $q_i$ 的值，交互库回答你的询问之后会将 $q$ 替换成 $q_i' = q_{p_i}$。最多 $2n$ 次询问，求出 $p$。
## Solution
我们注意到，对 $q$ 施加 $q_i = q_{p_i}$ 的变换这一过程的本质是一个置换。不妨盯着一个 $q_i$ 不放，我们发现其变换下去之后会为 $p_i, p_{p_i}, p_{p_{p_i}},\cdots$ 会形成一个环，环上 $u\to v$ 表示 $p_u = v$。那么我们就可以每次盯着一个没有求出答案的下标询问，把这部分环找到，这题就解决了。

询问次数的上界刚好为 $2n$，卡的很准。实际解决这道题目时千万记得打表找规律，可以加快找到答案的过程。
## Implementation

```cpp
const int maxn = 1e4 + 5;
int n, vis[maxn], ans[maxn];

int ask(int i) {
    cout << "? " << i << endl;
    int x; cin >> x;
    return x;
}

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        FOR(i, 1, n) vis[i] = 0;
        FOR(i, 1, n) {
            if (vis[i]) continue;
            vector<int> vec;
            int st = ask(i);
            vec.push_back(st);
            int u;
            do {
                u = ask(i);
                vec.push_back(u);
            } while (u != st);
            FOR(j, 0, (int)vec.size() - 2) {
                ans[vec[j]] = vec[j + 1];
                vis[vec[j]] = 1;
            }
        }
        cout << "! ";
        FOR(i, 1, n) cout << ans[i] << ' ';
        cout << endl;
    }
    return 0;
}
```



---

