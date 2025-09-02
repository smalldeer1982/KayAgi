# New Colony

## 题目描述

After reaching your destination, you want to build a new colony on the new planet. Since this planet has many mountains and the colony must be built on a flat surface you decided to flatten the mountains using boulders (you are still dreaming so this makes sense to you).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1481B/cfa82fc997bb3aa9f87fa07cb8193ccc436f5cb7.png)You are given an array $ h_1, h_2, \dots, h_n $ , where $ h_i $ is the height of the $ i $ -th mountain, and $ k $ — the number of boulders you have.

You will start throwing boulders from the top of the first mountain one by one and they will roll as follows (let's assume that the height of the current mountain is $ h_i $ ):

- if $ h_i \ge h_{i + 1} $ , the boulder will roll to the next mountain;
- if $ h_i < h_{i + 1} $ , the boulder will stop rolling and increase the mountain height by $ 1 $ ( $ h_i = h_i + 1 $ );
- if the boulder reaches the last mountain it will fall to the waste collection system and disappear.

You want to find the position of the $ k $ -th boulder or determine that it will fall into the waste collection system.

## 说明/提示

Let's simulate the first case:

- The first boulder starts at $ i = 1 $ ; since $ h_1 \ge h_2 $ it rolls to $ i = 2 $ and stops there because $ h_2 < h_3 $ .
- The new heights are $ [4,2,2,3] $ .
- The second boulder starts at $ i = 1 $ ; since $ h_1 \ge h_2 $ the boulder rolls to $ i = 2 $ ; since $ h_2 \ge h_3 $ the boulder rolls to $ i = 3 $ and stops there because $ h_3 < h_4 $ .
- The new heights are $ [4,2,3,3] $ .
- The third boulder starts at $ i = 1 $ ; since $ h_1 \ge h_2 $ it rolls to $ i = 2 $ and stops there because $ h_2 < h_3 $ .
- The new heights are $ [4,3,3,3] $ .

The positions where each boulder stopped are the following: $ [2,3,2] $ .

In the second case, all $ 7 $ boulders will stop right at the first mountain rising its height from $ 1 $ to $ 8 $ .

The third case is similar to the first one but now you'll throw $ 5 $ boulders. The first three will roll in the same way as in the first test case. After that, mountain heights will be equal to $ [4, 3, 3, 3] $ , that's why the other two boulders will fall into the collection system.

In the fourth case, the first and only boulders will fall straight into the collection system.

## 样例 #1

### 输入

```
4
4 3
4 1 2 3
2 7
1 8
4 5
4 1 2 3
3 1
5 3 1```

### 输出

```
2
1
-1
-1```

# 题解

## 作者：Microperson (赞：5)

# [题目传送门](https://www.luogu.com.cn/problem/CF1481B)

# 题目大意：
相信英文都能~~读懂~~

# 腐朽的思路：

也没啥特殊的地方，就是按照题目所说进行模拟即可。
题目中说要是巨石所滚下去的山要是没下一个高，巨石就滚不过去，所以说这块巨石就没了，但这座山的高度要加1，接着该抛下一块石头，问的是这些已有的石头可不可以到达最后。说到这里，就可很轻松的模拟出来了，这里我用$tmp$来记录每一块石头所能到达的位置。

# 新鲜出炉的code：

```
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#define N 100010
using namespace std;
int n,k,t,h[N];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		memset(h,0,sizeof(h));
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&h[i]); 
		}
		int tmp;
		while(k){
			tmp=1;
			for(int i=1;i<=n;i++)
			{
				if(h[i]>=h[i+1]){
					tmp++;
				} 
				if(h[i]<h[i+1]){
					h[i]+=1;k--;
					break;
				}
			}
			if(tmp>=n) {
				cout<<-1<<endl;
				break;
			}	
		}
		if(tmp<n) cout<<tmp<<endl;
	}
	return 0;
 } 
```


---

## 作者：kdy20100729 (赞：0)

### 题意简述：  
$n$ 座山排成一排，第 $i$ 座山的高度为 $h_i$。  
有 $k$ 个巨石依次从第一座山开始滚落，当某个巨石在第 $i$ 座山时：

>+ 如果 $i=n$ ，那么巨石就会被销毁。  
>+ 否则，如果 $h_i \geqslant h_{i+1}$，那么巨石继续滚到 $i+1$ 的位置。  
>+ 否则，巨石将在第 $i$ 座山停下，并将 $h_i$ 增加 $1$。  

目标：求出第 $k$ 个巨石会停在哪座山上，如果巨石被销毁了输出 ```-1```。

### 思路：  
其实就是一道模拟题。  
我们对于不会消失的巨石直接模拟求出它停在的山的编号，一旦碰到会被销毁的巨石就直接不用做后面的模拟，因为一旦有一个巨石被销毁了，后面的巨石也会滚到第 $n$ 座山然后全部被销毁。

### Code:  
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,pos,a[105];
int main()
{
    cin >> t;
    while(t--)
    {
        cin >> n >> k;
        for(int i=1; i<=n; i++)
            cin >> a[i];
        a[n+1]=0;
        while(k--)
        {
            pos=1;
            while(pos<=n&&a[pos]>=a[pos+1])
                pos++;
            a[pos]++;
            if (pos==n+1)
            {
                pos=-1;
                break;
            }
        }
        cout << pos << "\n";
    }
    return 0;
}
```

---

## 作者：DP王子 (赞：0)

我们观察到一个性质：如果一块石头滚进了垃圾桶，那么它后面滚下来的石头也必定会进入垃圾桶。

这是显然的，因为这块石头没有产生任何贡献，所以不会发生改变。

这样我们就可以暴力枚举每一块石头知道结束或者进入垃圾桶。当石头进入垃圾桶，代表输出 `-1`。

复杂度是 $O(t\times n\times h_i)$，可以过此题。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
int a[201];
inline int read()
{
	char C=getchar();
	int F=1,ANS=0;
	while (C<'0'||C>'9')
	{
		if (C=='-') F=-1;
		C=getchar();
	}
	while (C>='0'&&C<='9')
	{
		ANS=ANS*10+C-'0';
		C=getchar();
	}
	return F*ANS;
} 
int main()
{
	t=read();
	while (t--)
	{
		n=read(),k=read();
		for (int i=1;i<=n;i++) a[i]=read();
		int ans=-1;
		for (int i=1;i<=k;i++)
		{
			for (int j=1;j<n;j++)
			{
				if (a[j]<a[j+1]) 
				{
					a[j]++;
					ans=j;
					goto fff;
				}
			}
			cout << -1 << endl;
			goto eee;
			fff:;
		}
		cout << ans << endl;
		eee:;
	}
	return 0;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
$n$ 座山排成一行，其中第 $i$ 座山的高度为 $h_i$。

有 $k$ 个巨石依次从第一座山开始滚落。当某个巨石在第 $i$ 座山时：

- 如果 $i=n$，那么巨石直接消失。
- 否则，如果 $h_i\geqslant h_{i+1}$，那么巨石继续滚落。
- 否则，巨石将在第 $i$ 座山停下，并使得 $h_i$ 增加 $1$。

请求出第 $k$ 个巨石最终会落在哪座山上。

**数据范围：$t$ 组数据，$1\leqslant t,n,h_i\leqslant 100$，$\bf 1\leqslant k\leqslant 10^9$。**
## Solution
你以为这道题目 $k$ 在 $10^9$ 级别就不可做了？事实上 $k$ 到了一定的范围时，后面的巨石就会滚到第 $n$ 座山然后全部消失。于是我们对于不会消失的巨石直接模拟求出它落在的山的编号，一旦碰到会消失的巨石就直接不用做后面的模拟，因为如上文所述，后面的巨石会滚到第 $n$ 座山然后全部消失。
## Code
```cpp
namespace Solution {
	const int N = 107;
	int n, k, h[N];

	iv Main() {
		MT {
			read(n, k);
			F(int, i, 1, n) read(h[i]);
			int ans = 0;
			while(k--) {
				int fl = 0;
				F(int, i, 1, n) {
					if(i == n) {fl = 1; break;}
					if(h[i] < h[i + 1]) {h[i]++, ans = i; break;}
				}
				if(fl) {ans = -1; break;}
			}
			println(ans);
		}
		return;
	}
}

```

---

## 作者：huayucaiji (赞：0)

本题我在 14min 时通过，当时只有 647 人通过。

本题 $k$ 很大，其实是个纸老虎。我们想最简单的，如果有一次我的石头滚到了 $n+1$ 处，那么下一个，还会滚到 $n+1$ 处，因此我们只需要一直模拟，直到有石头滚到 $n+1$ 时，退出循环，答案为 $-1$。若 $k$ 次前，没有滚到 $n+1$ 处，把模拟得出的答案输出即可，可以证明，时间复杂度为 $O(\sum hn)$

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int MAXN=100+10;

int n,h[MAXN],k;

signed main() {
	int t=read();
	while(t--) {
		n=read();k=read();
		for(int i=1;i<=n;i++) {
			h[i]=read();
		}
		h[n+1]=0;
		
		bool flag=1;
		int pos;
		while(k--&&flag) {
			pos=1;
			while(pos<=n&&h[pos]>=h[pos+1]) {
				pos++;
			}
			h[pos]++;
			if(pos==n+1) {
				flag=0;
				pos=-1;
			}
		}
		cout<<pos<<endl;
	}
	return 0;
}


```

---

## 作者：xuezhe (赞：0)

可以发现有效操作次数不超过 $\sum h_i$，直接模拟到石头会掉出边界为止。

Code:

```cpp
int T,n,k,h[105];
int main(){
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=n;++i)
            cin>>h[i];
        int p(0);
        for(int t=1;t<=k;++t){
            int o(-1);
            for(int i=1;i<n;++i){
                if(h[i]<h[i+1]){
                    ++h[o=i];
                    break;
                }
            }
            p=o;
            if(o==-1)
                break;
        }
        cout<<p<<'\n';
    }
    return 0;
}
```



---

## 作者：fanfansann (赞：0)

## B - New Colony
有 $n$ 座山，输入这 $n$ 座山的高度 $h_i$，你在第一座山上，有 $k$ 块石头，你依次在第一座山上，丢下这些石头。

石头会按照下面的行为走（假设当前石头在第 $i$ 座山上）：

- 若 $h[i] \ge h[i + 1]$  则石头会滚到 $i+1$ 座山上，并且根据 $i+1$ 座山的情况，继续走。若到达最后一座山上(第 $n$ 座山) ，就会掉进回收站里。
- 若 $h[i] <h[i + 1]$  石头会停下来，掉在第 $i$ 座山上，并且留下来，使得第 $i$ 座山的高度 $+1$。


请问第 $k$ 个石头会在哪里？若在回收站里输出 `-1` ，否则输出所在山的编号。

$1 \le t \le 100,1 \le n \le 100,1 \le k \le 10^9,1 \le h_i \le 100$

**Solution**


$k$ 很大很大，但是 $h$ 和 $n$ 都很小，所以可以直接暴力模拟即可。

反正一旦到了最后一座山就直接输出 `-1` 即可。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;
const int N = 5e7 + 7, mod = 1e9 + 7;
typedef long long ll;
typedef int itn;

itn n, m, q, d, k;
itn t;
int h[N];

void solve()
{
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; ++ i) {
        scanf("%d", &h[i]);
    }
    itn now = -1;
    for(int i = 1; i <= k; ++ i) {
        for(int j = 0; j < n; ++ j) {
            if(j + 1 == n) {
                puts("-1");
                return ;
            }
            else if(h[j] < h[j + 1]) {
                now = j + 1;
                h[j] ++ ;
                break;
            }
        }
    }
    printf("%d\n", now);
}

int main()
{
    scanf("%d", &t);
    while(t -- ) {
        solve();
    }
    return 0;
}
```

---

## 作者：Sora1336 (赞：0)

发现这题的 $k$ 很大，但是其实并不用惧怕它。

发现只要到了一块石头滚进了垃圾桶时，那么后面的石头也会进垃圾桶，这时跳出循环就好了，并输出 `-1`。

但是如果没滚进垃圾桶，那么就模拟得出答案。

```cpp
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;
int main() {
	int t;
	cin >> t;
	while(t --) {
		bool flg=0;
		int a[105], n, k, ok = 0, sum = 0;
		cin>>n>>k;
		for(int i = 1; i <= n; i ++) cin >> a[i];
		while(1) {
			for(int i = 1; i <= n; i ++) {
				if(i == n) {
					flg = 1;
					break;
				} if(a[i] < a[i + 1]) {
					a[i] ++, sum ++;
					if(sum >= k) ok = i;
					break;
				}
			}
			if(ok || flg) break;
		}
		if(ok){
			cout<<ok<<endl;
			continue;
		} else if(flg) puts("-1");
	}
}
```

---

