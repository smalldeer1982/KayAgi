# Even-Odd Game

## 题目描述

During their New Year holidays, Alice and Bob play the following game using an array $ a $ of $ n $ integers:

- Players take turns, Alice moves first.
- Each turn a player chooses any element and removes it from the array.
- If Alice chooses even value, then she adds it to her score. If the chosen value is odd, Alice's score does not change.
- Similarly, if Bob chooses odd value, then he adds it to his score. If the chosen value is even, then Bob's score does not change.

If there are no numbers left in the array, then the game ends. The player with the highest score wins. If the scores of the players are equal, then a draw is declared.

For example, if $ n = 4 $ and $ a = [5, 2, 7, 3] $ , then the game could go as follows (there are other options):

- On the first move, Alice chooses $ 2 $ and get two points. Her score is now $ 2 $ . The array $ a $ is now $ [5, 7, 3] $ .
- On the second move, Bob chooses $ 5 $ and get five points. His score is now $ 5 $ . The array $ a $ is now $ [7, 3] $ .
- On the third move, Alice chooses $ 7 $ and get no points. Her score is now $ 2 $ . The array $ a $ is now $ [3] $ .
- On the last move, Bob chooses $ 3 $ and get three points. His score is now $ 8 $ . The array $ a $ is empty now.
- Since Bob has more points at the end of the game, he is the winner.

You want to find out who will win if both players play optimally. Note that there may be duplicate numbers in the array.

## 样例 #1

### 输入

```
4
4
5 2 7 3
3
3 2 1
4
2 2 2 2
2
7 8```

### 输出

```
Bob
Tie
Alice
Alice```

# 题解

## 作者：洛璟 (赞：7)

## Solution：

一开始我们会简单地想到Alice一直拿偶数的最大，Bob拿奇数最大即可。

然后我们看到样例的第二组：

```
3
3 2 1

输出：Tie
```

我们并不清楚是否能拿对面的数字，即Alice拿奇数，Bob拿偶数，但是我们看到此样例时，也会去考虑这个问题。

我们可以发现，如果Alice拿了2，那么易证她必输，因此我们不难想到：如果把对面的数字拿了，Alice最多就可以拿到2，那么Alice也是可以赢的。

于是Alice拿了3。

那么如果此时Bob拿了1，那么也是易证他必输。

于是他拿了2。

结果？两人都是零，开心地~~爆零~~平局了。

那么我们可以得出，在某些时刻拿对方的数字也是不错的，即使自己啥都得不到。

然后我们思维就会想到全拿最大的数即可，但是无法证明其正确性。

那么我们尝试着这样想：Alice拿走了对方的数字，相当于对方无法拿到这个数字。我们设Alice的可以拿到的数总和为 $x$，Bob为 $y$。假设Bob本来是可以拿到这个数字 $a$ 的，但由于Alice拿走了，导致Bob无法得到 $ a $，相当于 $y-a$ （本来这个 $y$ 中应当是包含a的），那么 $x-(y-a)$（做差法比较两数大小）就等于 $ x+a-y $，也就等于Alice拿走了 $a$，这样一来，Alice和Bob不再有奇偶之分。

### 因此，只要一直拿最大的那个数就行了。

那么代码实现也很简单：
```cpp
//洛璟の代码用ans作两个数之差，若Alice得分则加上这个数，
//Bob得分减去这个数，若答案为0则为平局，大于零则Alice胜，
//反之则Bob胜，其核心思想为作差法
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int t,n;
int a[1919810];
inline int read()
{
    int x=0,f=1;
    char c=getchar();
    while(c<'0' || c>'9')
    {
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0' && c<='9')
    {
        x=(x<<3)+(x<<1)+(c^'0');
        c=getchar();
    }
    return x*f;
}
bool cmp(int a,int b)
{
    return a>b;
}
signed main()
{
    t=read();
    while(t--)
    {
        int ans=0;
        n=read();
        for(int i=1;i<=n;i++)
        {
            a[i]=read();
        }
        sort(a+1,a+n+1,cmp);//先排序，保证他们拿的数永远是当前最大的
        for(int i=1;i<=n;i++)
        {
            if(a[i]%2==0 && i%2==1) ans+=a[i];//从大到小拿，按规则来计算加分
            else if(a[i]%2==1 && i%2==0) ans-=a[i]; //同上
        }
        if(ans>0) printf("Alice\n");//详见开头
        else if(ans==0) printf("Tie\n");
        else printf("Bob\n");
    }
    return 0;
}
```

---

## 作者：LeavingZzz (赞：5)

# $\mathsf{Solution\space To\space CF1472D}$  
复健Div3  
## $\mathsf{Description}$  
Alice 和 Bob 玩游戏，给出 $n$ 个整数 $\{a\}$，Alice 先手，每次 Alice 从剩余的数字中选择一个数字删去，如果这个数字是偶数那么 Alice 得分加上这个数字，否则 Alice 不加分，然后 Bob 选择一个数字删去，如果这个数字是奇数那么 Bob 得分加上这个数字，否则 Bob 不加分  
当 Alice 和 Bob 都用最优策略时，输出最后得分高的一位，或者输出平局

$1\le n \le 2\times 10^5,1\le a_i\le 10^9$  
## $\mathsf{Solution}$  
发现每次选择数字的时候一定选择奇数集合或者偶数集合中的最大值  
实际上就是抢自己集合的最高分或者把对方的最高分拿走不让对方得  

最后我们只关注 Alice 分高还是 Bob 分高  
设 Ailce 得分为 $x$，Bob 得分为 $y$  
如果有 $2x<2y$，那么也一定有 $x<y$   
如果有 $x+d<y+d$，那么也一定有 $x<y$  
拿着这两个东西就能把这题做出来    

一开始我们把 $x$ 初始化为所有偶数的和，$y$ 为所有奇数的和  

每次选取数字的时候，如果选取的自己的集合（即 Alice 选偶数，Bob 选奇数），那么就直接加，这样算出来的分数是实际分数的两倍（初始 Alice 都拿到了偶数 Bob 拿到了奇数，这里再加一次就是两倍），由上面的第一个结论可以知道不会对判断造成影响  

如果选取对方的集合（即 Alice 选奇数，Bob 选偶数），也直接加在自己的得分上，这样不会对结果的判断造成影响，因为选取对方的集合相当于给对方得分减掉这个数字（初始认为 Bob 拿到了所有的奇数而 Alice 拿到了所有的偶数，如果被对方选走的话就要减掉对应的值），而这时候让 $x$ 和 $y$ 同时加上这个数字（根据第二个结论，这也是对的），就相当于只对自己的得分加上这个数字  


------------
这样算出来最后谁分高谁就是win  

每次选数无论选取的是奇数还是偶数计算时都是加到自己的得分上，采取最优策略所以每次选取剩余数字的最大值即可  

所以一开始初始化得分后把所有数字排序，按照 Alice->Bob->Alice->Bob...的顺序依次选取最后比较即可  
## $\mathsf{Code}$  
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
#include<cstdlib>
#include<ctime>
using namespace std;
const int maxn=200007;
int T,N;
int A[maxn];
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    #endif
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);
        long long Al=0,Bo=0;//二人得分
        for(int i=1;i<=N;i++)
        {
            scanf("%d",&A[i]);
            if(A[i]&1) Bo+=A[i];//初始化Bob拿奇数
            else Al+=A[i];//初始化Alice拿偶数
        }
        sort(A+1,A+1+N);
        int op=0;
        for(int i=N;i>0;i--,op^=1)
        {
            if(op) Bo+=A[i];//依次选取（注意Alice先手）
            else Al+=A[i];
        }
        //判断即可
        if(Al==Bo) puts("Tie");
        else if(Al>Bo) puts("Alice");
        else puts("Bob");
    }
    return 0;
}
```

---

## 作者：Phartial (赞：1)

## [传送门](https://www.luogu.com.cn/problem/CF1472D)
## 思路
- 我们可以先让Alice取所有的偶数，Bob取所有的奇数，这样就可以把不平衡博弈转为平衡博弈
- 然后Alice和Bob依次取最大的数
## 代码
```cpp
#include <iostream>
#include <algorithm>
```
```cpp
using namespace std;
```
```cpp
const int kMaxN = 2e5 + 1;
```
```cpp
long long a[kMaxN], s[2];
int t, n;
```
```cpp
int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    s[0] = s[1] = 0;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      s[a[i] & 1] += a[i];
    }
    sort(a + 1, a + 1 + n);
    for (int i = 0; i < n; i++) {
      s[i & 1] += a[n - i];
    }
    if (s[0] == s[1]) {
      cout << "Tie" << endl;
    } else {
      cout << (s[0] > s[1] ? "Alice" : "Bob") << endl;
    }
  }
  return 0;
} 
```



---

## 作者：杳冥 (赞：1)

## Solution
一开始想的策略是 $Alice$ 有偶数就拿最大的偶数，没有偶数再拿最大的奇数，可是这种策略样例的第二组都过不了。思考一下，如果现在有两个数 $x$ 和 $y$ 且 $x>y$，如果 $Alice$ 先拿，且 $x$ 为奇数，$y$ 为偶数，那么按照刚才想的策略，$Alice$ 肯定要先拿 $y$ ，下一轮到了 $Bob$ 他就会拿走 $x$ 。所以，$Bob$ 的得分就比 $Alice$ 多了 $x-y$ 分。其实如果 $Alice$ 先拿 $x$ 的话，他们就都得了0分，平局。所以得到最优的策略。

## 具体操作
先将给出的数列排序，**每次不管谁拿，都要拿最大的数**，拿的时候分别记录两个人的得分，最终再比较得分。
## Code
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#define ll long long
#define pn putchar('\n')
using namespace std;
const int maxn=2e5+10;
priority_queue<int> b;
inline int rd(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int t,n,k;
ll aa=0,bb=0,p=0,q=0,tot=1;
int cmp(int a,int b){return a>b;}
int main(){
	t=rd();
	while(t--){
		while(!b.empty()){b.pop();}
		tot=1;p=0,q=0;aa=0;bb=0;
		n=rd();
		for(int i=1;i<=n;++i){
			k=rd();
			if(k%2==0) aa+=k;
			else bb+=k;
			b.push(k);
		}
		if(bb==0 && aa!=0){
			printf("Alice");pn;
			continue;
		}
		if(aa==0 && bb!=0 && n>=2){
			printf("Bob");pn;
			continue;
		}
		//sort(a+1,a+n+1,cmp);
		while(tot<=n){
			if(tot%2==1){
				if(b.top()%2==1) b.pop();
				else{
					p+=b.top();b.pop();
				}
			}
			else{
				if(b.top()%2==0) b.pop();
				else{
					q+=b.top();b.pop();
				}
			}
			tot++;
		}
		if(p<q){printf("Bob");}
		if(p>q){printf("Alice");}
		if(p==q){printf("Tie");}
		pn;
	}
	return 0;
}
```


---

