# Prime XOR Coloring

## 题目描述

You are given an undirected graph with $ n $ vertices, numbered from $ 1 $ to $ n $ . There is an edge between vertices $ u $ and $ v $ if and only if $ u \oplus v $ is a [prime number](https://en.wikipedia.org/wiki/Prime_number), where $ \oplus $ denotes the [bitwise XOR operator](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Color all vertices of the graph using the minimum number of colors, such that no two vertices directly connected by an edge have the same color.

## 说明/提示

In the first test case, the minimum number of colors is $ 1 $ , because there is only one vertex.

In the second test case, the minimum number of colors is $ 2 $ , because there is an edge connecting $ 1 $ and $ 2 $ ( $ 1 \oplus 2 = 3 $ , which is a prime number).

In the third test case, the minimum number of colors is still $ 2 $ , because $ 2 $ and $ 3 $ can be colored the same since there is no edge between $ 2 $ and $ 3 $ ( $ 2 \oplus 3 = 1 $ , which is not a prime number).

In the fourth test case, it can be shown that the minimum number of colors is $ 3 $ .

In the fifth test case, it can be shown that the minimum number of colors is $ 3 $ .

In the sixth test case, it can be shown that the minimum number of colors is $ 4 $ .

## 样例 #1

### 输入

```
6
1
2
3
4
5
6```

### 输出

```
1
1
2
1 2
2
1 2 2
3
1 2 2 3
3
1 2 2 3 3
4
1 2 2 3 3 4```

# 题解

## 作者：jhdrgfj (赞：6)

我会做诈骗题！

一个很显然的想法就是奇偶分析。考虑奇偶性相同的两个数异或起来一定是偶数，所以若奇偶性相同则只有二进制下相差一个 $2$ 的两数会连边。稍微画一下可知图长这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/416x8ox3.png)

然后我们发现上面用两种不同颜色就够了，下面若再用另外两种颜色，则奇数偶数间的边颜色也不同。所以答案一定不会超过四，可以用 ``1 3 2 4`` 的循环染色。

样例也很贴心的告诉我们不满四种颜色的所有情况。复制样例即可。

然后就做完了。我爱做诈骗题。

[代码。](https://codeforces.com/contest/1991/submission/273265135)

---

## 作者：AKPC (赞：5)

情商考验题，如果情商低可能会想到结论不敢交。

以下只考虑 $n\geq6$ 的情况。

首先，颜色数量肯定不会 $<4$，因为题目的样例给出来了。

其次，如果考虑对 $i$ 节点染上 $(i-1)\bmod4+1$ 颜色，那么对于任意两个 $i,j$ 满足 $i\equiv j\pmod4$，有 $i\oplus j\bmod4=0$，即 $4\mid(i\oplus j)$，这是显然的。然而，对于一个 $4$ 的倍数，其一定不是素数，故最小颜色数量不可能 $>4$。

这种方式也同时证明了 $1,2,3$ 作为颜色数量是不可行的，因为 $1,2,3$ 各自的倍数都有可能是素数。

对于 $n<6$，利用样例打表即可。

---

## 作者：_lmh_ (赞：4)

注意到如果两个整数之差为 4 的倍数，那么他们异或也一定是 4 的倍数，显然是合数。

所以我们就有了四种颜色的万能方案。

观察样例，$n=6$ 就需要四种颜色，于是对更小的数据特判即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll T,n;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		if (n<=5){
			cout<<n/2+1<<endl;
			for (int i=1;i<=n;++i) cout<<i/2+1<<' ';cout<<endl;
		}
		else{
			cout<<4<<endl;
			for (int i=1;i<=n;++i) cout<<(i%4)+1<<' ';cout<<endl;
		}
	}
	return 0;
}
```

---

## 作者：2huk (赞：1)

翻译官解。

**题意**：给定一张图。若 $u \oplus v$ 为质数则 $u, v$ 间有一条连边。求最少颜色数，使得将图染色后，没有一条边的两个端点的颜色相同，并给出每个点的染色方案。

**做法**：

对于 $n \le 5$ 的情况，复制样例答案即可。

对于 $n \ge 6$ 的情况，我们断言答案为 $4$。证明如下：

> 首先答案必定 $\ge 4$。因为 $1, 3, 4, 6$ 两两异或都是质数。
>
> 其次等号可以取到。考虑这种染色方式：将点 $i$ 染色成 $i \bmod 4 + 1$。那么若 $u, v$ 同色，即若 $u \equiv v \pmod 4$，那么它们在二进制表示下，最后 $2$ 位一定是相同的。那么 $u \oplus v$ 的最后两位一定都是 $0$。显然这个异或值是 $4$ 的倍数，不可能是质数。
>
> 综上答案为 $4$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

typedef long long ll;

signed main() {
	int T;
	cin >> T;
	while (T -- ) {
		int n;
		cin >> n;
		if (n == 1) {
			cout << 1 << '\n';
			cout << 1 << '\n';
		}
		else if (n == 2) {
			cout << 2 << '\n';
			cout << 1 << ' ' << 2 << '\n';
		}
		else if (n == 3) {
			cout << 2 << '\n';
			cout << 1 << ' ' << 2 << ' ' << 2 << '\n';
		}
		else if (n == 4) {
			cout << 3 << '\n';
			cout << 1 << ' ' << 2 << ' ' << 2 << ' ' << 3 << '\n';
		}
		else if (n == 5) {
			cout << 3 << '\n';
			cout << 1 << ' ' << 2 << ' ' << 2 << ' ' << 3 << ' ' << 3 << '\n';
		}
		else {
			cout << 4 << '\n';
			for (int i = 1; i <= n; ++ i ) {
				cout << i % 4 + 1 << ' ';
			}
			cout << '\n';
		}
	}
	return 0;
}
```

---

## 作者：_O_v_O_ (赞：1)

神金场的逆天构造题。

我们可以令 $a_i$ 为 $i\bmod 4+1$，因为这样对于任意颜色相同的 $(i,j)$，$i\oplus j$ 一定是 $4$ 的倍数，很明显这对于 $n\ge 6$ 时是最优的。

对于 $n<6$，我们注意到可以用更少的颜色，然后我们就发现了样例已经给我们了方案，那么这题就做完了。

---

## 作者：白鲟 (赞：1)

非常诈骗的一个题目。可以猜想染色数不会很多。题目的描述可以转化为同色的数间都不存在连边。一个朴素的想法是奇数同种颜色，偶数同种颜色，这样可以让同色的异或结果为偶数，但由于 $2$ 的存在推翻了这一想法的正确性。由样例可知对于较大的 $n$ 至少需要 $4$ 种颜色。稍加思索，发现按照 $4$ 的同余类染色，就可以使得同色的异或结果为 $4$ 的倍数，必定不是质数，问题到此解决。
```cpp
#include <cstdio>
int T, n;
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        switch (n) {
        case 1:
            printf("1\n1\n");
            break;
        case 2:
            printf("2\n1 2\n");
            break;
        case 3:
            printf("2\n1 2 2\n");
            break;
        case 4:
            printf("3\n1 2 2 3\n");
            break;
        case 5:
            printf("3\n1 2 2 3 3\n");
            break;
        default:
            printf("4\n");
            for (int i = 1; i <= n; ++i)
                printf("%d ", (i - 1) % 4 + 1);
            puts("");
            break;
        }
    }
    return 0;
}
```

---

## 作者：Reunite (赞：1)

构造场被创飞了。

注意到，随着 $n$ 增加，需要的颜色数不减，又由样例，$n=6$ 时需要 $4$ 种颜色，因此 $n\ge 6$ 时，至少需要 $4$ 种颜色。

发现如果不考虑质数 $2$，那么只需要奇偶染色即可，那我们能不能把对 $2$ 取模分组，改为对 $4$ 取模分组？显然是可以的，我们就染成 $col_i=i\bmod 4+1$。注意到这个时候，任意两个同色的数异或至少是 $4$ 倍数，所以是合法的。$n\le 5$ 输出样例，否则如上构造即可。

代码实现略有区别。

---

```cpp
 if(n<=5){
	printf("%d\n",n/2+1);
	printf("1 ");
	int x=2;
	for(int i=2;i<=n;i++){
		printf("%d ",x);
		if(i&1) x++;
	}
	puts("");
}
else{
	puts("4");
	int x=1;
	for(int i=1;i<=n;i++){
		printf("%d\n",x);
		x++;
		if(x==5) x=1;
	}
	puts("");
}
```

---

## 作者：yyz1005 (赞：0)

被构造创飞了。

首先注意到：

$$1 \oplus 3 = 2,1 \oplus 4 = 5,1 \oplus 6 = 7 \\ 3 \oplus 4 = 7,3 \oplus 6 = 5,4 \oplus 6 = 2$$

也就是说 $1,3,4,6$ 构成一个完全子图，$n \ge 6$ 时颜色数至少为 $4$。

又注意到若 $x \equiv y ( \bmod 4 )$，应有 $x \oplus y$ 二进制下末三位均为 $0$，也就是说 $4 | x \oplus y$，因此 $n \ge 6$ 时对所有模 $4$ 相同的项涂同一种颜色就行了，即 $2,3,4,1,2,3,4,1,\cdots$。

$n \le 5$ 的情况就是样例，结束了。

[Submission #273263794 - Codeforces](https://codeforces.com/contest/1991/submission/273263794)

---

## 作者：lfxxx (赞：0)

非要放一堆构造吗？

考虑对于 $n > 6$ 的情况，显然颜色数至少 $4$ 种，然而把所有数按照模 $4$ 分成 $4$ 类后显然每一类中间的数异或后二进制下最低位与次低位均为 $0$，一定是 $4$ 的倍数也就是不可能是质数，所以直接染 $4$ 种颜色即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
bool isPrime(int a){
    if(a<2) return 0;
    for(int i=2;i*i<=a;i++)
    if(a%i==0) return 0;
    return 1;
}
int n;
void work(){
    cin>>n;
    if(n>6){
        cout<<4<<'\n';
        for(int i=1;i<=n;i++) cout<<i%4+1<<' ';
        cout<<'\n';
        return ;
    }
    int cnt=1;
    for(int i=1;i<=n;i++){
        if(isPrime(1^i)==true&&i!=3) cnt++;
    }
    cout<<cnt<<'\n';
    int t=1;
    for(int i=1;i<=n;i++){
        if(isPrime(1^i)==true&&i!=3) t++;
        cout<<t<<' ';
    }
    cout<<'\n';
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
}

```

---

