# 青木君のいたずら

## 题目描述

有一个初始值为 $1$ 的变量 $x$，高桥决定进行 $30$ 次将 $x$ 乘以 $3$ 的操作。但是青木君却做了一个恶作剧。他选择了一个满足 $1\le k \le30$ 的整数 $k$，在高桥进行完第 $k$ 次操作后将 $x$ 加上了 $1$ 。直到高桥完成了全部操作后他才发现了不对劲。他想让你帮帮他，求出青木选择的 $k$ 的值是多少？但还有一种可能，那就是青木在高桥完成所有操作后直接把 $x$ 换成了另一个数。如果是这样，请输出 $-1$。

## 说明/提示

**数据规模与约定**

$1 \le n \le 10^{15}$，$n \neq 3^{30}$，且 $n$ 为整数。

## 样例 #1

### 输入

```
205894618879050```

### 输出

```
10```

## 样例 #2

### 输入

```
314159265358979```

### 输出

```
-1```

# 题解

## 作者：linch (赞：4)

看到大佬们都是用 C++，本蒟蒻就来一篇 Python 题解。
## 题意
一个整数 $1$，要将他执行 $30$ 次乘 $3$ 的操作。但是在一次操作执行完成后将这个数加上了 $1$。让你找出这次操作是第几次。如果数字在最后被替换就输出 $-1$。输入为最终执行完成的整数。

## 解决
很明显，我们可以倒推着求，每次将他除以 $3$。如果出现该数除以 $3$ 的余数为 $2$ 时，那么肯定无解。或者一共出现 $2$ 次及以上的除以 $3$ 的余数为 $1$ 时，也是无解。否则，如果最后的结果刚好为 $1$，那么有解。这是因为数据不可能是 $3^{30}$，所以必定有一次操作。

## 代码
难度不大，直接模拟。具体看代码注释。
```python
x=int(input())
i=30
# 循环30次，注意是倒着来
f=0
ans=0
#初始化
while i>0:
    if x%3==2:
        print("-1")
        exit()
    # 如果出现该数除以 3 的余数为 2，输出 -1 并退出
    elif x%3==1:
        if f==1:
            print("-1")
            exit()
        # 如果出现该数第 2 次除以 3 的余数为 1，输出 -1 并退出
        else:
        # 记录已经有一次除以 3 的余数为 1，注意要将数字 -1，并且将目前将答案设为当前的 i。
            f=1
            ans=i
            x=x-1
    # 把 x 除以 3。
    x=x/3
    # 把 i 减去 1，继续循环
    i=i-1
# 如果最后为 1，输出储存的答案。
if x==1:
    print(ans)
# 否则就无解
else:
    print("-1")
```

---

## 作者：Pink_Cut_Tree (赞：3)

### 解题思路

当这个数模 $3$ 余 $2$，或者有 $2$ 次（或以上）的模 $3$ 余 $1$，答案输出 ```-1```。

其余情况，输出操作后的 $x$ 。

### 操作说明

每次操作，将 $x$ 除以 $3$ ，操作完毕之后，如果这个数是 $1$ ，证明有解，否则无解，仍然输出 ```-1```。

### 特别注意：

$ 1\ \leq\ N\ \leq\ 10^{15} $，所以要开 ```long long```。

### 代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main(){
	bool flag=false;
	long long x; long long ans=-1;
	scanf("%lld",&x);
	for(long long i=30;i>=1;i--){
		if(x%3==2){
			printf("-1\n"); return 0;
		}
		else if(x%3==1){
			if(flag){
				printf("-1\n"); return 0;
			}
			ans=i; x--; flag=true;
		}
		x/=3;
	}
	if(x==1){
		printf("%lld",ans);
	}
	else{
		printf("-1\n");
	}
return 0;
}
```



---

## 作者：xiaofeng_and_xiaoyu (赞：2)

考虑最后只可能有三十种答案（和 $-1$ ），只需要进行一次遍历存储所有答案，然后扫一遍进行对比就可以了。

预处理复杂度平方级，查询复杂度常数级。

足以通过本题。

如果压行，可以压到十五行，但这里为了~~方便复制~~美观，展示出了 $28$ 行的普通代码（码量很小，如果抄题解建议自己打）。

```cpp
#include<iostream>
using namespace std;
int main(){
	long long int a,b=0;
	cin>>a;
	for(int i=0;i<30;i++){
		if(a%3==2){
			cout<<-1<<endl;
			return 0;
		}else if(a%3==1){
			if(b){
				cout<<-1<<endl;
				return 0;
			}else{
				b=i;
				a-=1;
				a/=3; 
			}
		}else{
				a/=3;
		}
	}
	if(a==1){
		cout<<30-b<<endl;
	}else{
		cout<<-1<<endl;
	}
} 
```


---

## 作者：Loser_Syx (赞：2)

## 思路

对于输出 $-1$ 的情况，有如下几种可能：

- 这个数 $\bmod$ $3 = 2$。

- 这个数有过至少 $2$ 次的 $\bmod$ $3 = 1$。

注意，当此数 $\bmod$ $3 = 1$ 时，我们要将其 $-1$，并记录位置。

每次操作完要将此数 $\div 3$。

如果最后那个数是 $1$，证明有解，输出记录的位置。

其他情况也是输出 $-1$。

## 代码

```cpp
#include <iostream>
#define int long long
using namespace std;
bool flag = 0;//记录有没有减一过了
main(){
    int x, ans = -1;
    cin >> x;
    for(int i = 30; i >= 1; i--){
        if(x % 3 == 2){//余2的肯定不满足
            cout << -1 << endl;
            return 0;
        }
        else if(x % 3 == 1){
            if(flag){//只能减一次1
                cout << -1 << endl;
                return 0;
            }
            ans = i;
            x -= 1;
            flag = 1;
        }
        x /= 3;
    }
    if(x == 1) cout << ans << endl;//x=1说明这个数字是没被更换的
    else cout << -1 << endl;
    return 0;
}
```

---

## 作者：liusiqi10 (赞：1)

### 题意理解
有一个初始值为 $1$ 的变量 $x$，对 $x$ 进行 $30$ 次乘 $3$ 的操作。在第 $k (1\le k \le 30)$ 次操作后将结果 $+1$，然后继续进行操作。已知最终结果，求 $k$ 的值。

### 题目分析
像我这种 _**蒟蒻**_ 最先想到的方法就是枚举，反正 $k$ 最多就到 $30$，肯定不会超时。具体地说，进行完 $k$ 次操作后，结果是 $3^k$，再将结果 $+1$，然后继续进行 $30-k$ 次操作，也就是将结果乘以 $3^{30-k}$，最终结果是 $(3^k+1) \times 3^{30-k}$。

#### 话不多说，直接贴代码（仅供参考，请勿抄袭）
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long n; //此数据范围需要开long long
	int k;
	cin>>n;
	for(int k=1;k<=30;k++) //从1到30依次枚举k
	{
		long long tmp=(pow(3,k)+1)*pow(3,30-k); //计算结果，pow(x,y)表示x^y
		if(tmp==n)//结果一样就输出并结束程序
		{
			cout<<k;
			return 0;
		}
	}
	cout<<-1;	//找不到就输出-1
	return 0;
}
```

---

## 作者：LYJ_B_O_Creation (赞：1)

## 思路

先算出每一种会被青木君做恶作剧将数 $+1$ 的可能，用 `map` 存储每一种可能，值写在第几次加的 $1$。然后再判断 $x$ 是否有值，如果有，直接输出，如果没有，就是青木君改掉了这个数，输出 $-1$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long//注意要开long long
using namespace std;
map<int , int> MAP;
void times(int a , int I)//创建函数
{
	for(int i = I + 1;i <= 30;i++) 
	{
		a *= 3;
	}
	MAP[a] = I;
}
main()
{
	int x;
	cin >> x;
	int ans = 1;
	for(int i = 1; i <= 30; i++)
	{
		ans *= 3;
		times(ans + 1 , i);
	}
	if(MAP[x] > 0) //如果MAP[x]大于0，那么输出MAP[x]
	{
		cout << MAP[x] << endl;
	}
	else //否则输出-1
	{
		cout << -1 << endl;
	}
	return 0;
}
```

---

## 作者：zhanghaosong (赞：1)

# AT_past202107_e 青木君のいたずら 题解

### 题意简述

这是这道题的本质内容：

> 令这个数为 $x$，如果 $x \text { mod } 3=2$ 或有两次及以上的 $x \text { mod } 3=1$，就输出 `-1`。否则输出操作后的 $x$。而每次只需要讲 $x$ 除以 $3$ 即可。

### 注意

1. 看数据范围，$1\leq n \leq 10^{15}$，需要开 `long long`。

1. 最多需要循环 $30$ 次。注意读题。

### 代码

请自己实现（逃）。

---

## 作者：mz2022 (赞：0)

[我是传送门](https://www.luogu.com.cn/problem/AT_past202107_e)

解题思路：
--------
将 $x$ 不断除以 3，如果 $x \bmod 3 = 2$ 或者有两次及以上的 $x \bmod 3 = 1$，直接输出 $-1$。

如果最后的 $x$ 为 $1$，输出第一次 $x \bmod 3 = 1$ 时的操作次数，否则输出 $-1$。

注意事项：
--------

记得开 long long。

AC Code:
--------
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,ok,ans;
signed main()
{
	cin>>n;
	for(int i=30;i>=1;i--)
	{
		if(n%3==1)
		{
			if(ok)
			{
				cout<<-1;
				return 0;
			}
			else 
			{
				ok=1;
				ans=i;
				n--;
			}
		}
		if(n%3==2)
		{
			cout<<-1;
			return 0;
		}
		n/=3;
	}
	if(n==1)cout<<ans;
	else cout<<-1; 
	return 0;
} 
```

---

## 作者：zxh923 (赞：0)

# AT_past202107_e 青木君のいたずら 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_past202107_e)

### 思路

首先有一个结论，若 $x$ 是 $3$ 的倍数，青木把 $x+1$，乘 $3$ 之后他一定还是 $3$ 的倍数。

由此我们便可以从 $30$ 次出发，把 $x$ 的最终值每次除以 $3$。

如果余 $1$，我们把计数器增加 $1$，当计数器超过 $1$ 时，直接输出 `-1` 即可。

如果余 $2$，那么青木一定改了这个数，直接输出 `-1` 即可。

但是还有一种情况，导致我栽了好多次。如果前面一切顺利，$30$ 次除以 $3$ 的运算完成后，结果不是 $1$ 怎么办？显然也要输出 `-1`。

还有注意一点，数据范围最大可达 $10^{15}$，所以我们要开 **long long**，这点非常重要！

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long x,cnt,ans,jsq;//记得开long long
int main(){
   cin>>x;
   for(int i=30;i>=1;i--){//只有30次运算
	   if(x%3==1){//余1的情况
	        cnt++;
	        ans=i;
	   }
	   if(cnt>=2){//计数器大于1直接输出-1
	        cout<<-1<<'\n';
	        return 0;
	   }
	   if(x%3==2){//余2直接输出-1
	        cout<<-1<<'\n';
	        return 0;
	   }
	   x/=3;
   }
   if(x==1)cout<<ans<<'\n';
   else cout<<-1<<'\n';//运算后不是1也要输出-1
   return 0;
} 
```


---

## 作者：awdereye (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_past202107_e)
### 解题思路
本题输出为 `-1`的情况：

-  $x \bmod 3 = 2$ 时。
-  $x \bmod 3 = 1$ 的情况出现两次。
- 最后 $x\ne1$ 时。

本题题解采用思路为**函数递归**，定义 $f(a,now)$ 函数，其中 $a$ 代表使用函数是除以的数， $now$ 代表到了第几次，如果出现上述情况就输出 `-1` 并 `return ;`。
### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,qwq;
bool flag=0;
void fun(long long a,long long now){
		n=a;
		if(now==0){
			if(a==1){//为一输出
				cout<<qwq;
			}
			else{
				cout<<-1;
			}
			return ;
		}
		if(a%3==2){
			cout<<-1;//直接输出
			flag=1;
			return ;
		} 
		else if(a%3==1){
			if(flag){
				a--;
				cout<<-1;
				flag=0;
				return ;
			}
			a--;
			flag=1;
			qwq=now;//记录次数
		} 
		fun(a/3,now-1);
}
int main(){
		cin>>n;
		fun(n,30);
		return 0;
}

```
### [验证](https://www.luogu.com.cn/record/118083553)


---

## 作者：回声之歌 (赞：0)

- 总体思路：倒推法还原每次操作后的 $x$。题意中对初始值为 1 的变量 $x$ 进行了 30 次乘 3 操作，则此时对最后的 $x$ 进行 30 次除以 3 操作。若将 $x$ 成功还原至 1，输出求得的 $k$ 值，否则输出 -1。

- 在非 -1 情况下，对于 $\forall i \in \left[1, n \right]$，第 $i$ 次操作后的 $x$ 必由第 $i - 1$ 次操作的 $x$ 乘 3 或乘 3 加 1 得到，则对于第 $i$ 次操作后的 $x$，必有 $x \bmod 3 = 0$ 或 $x \bmod 3 = 1$。因此倒推时，在每次除以 3 操作前需先计算 $x \bmod 3$ 值，若为 1，则 $k = i$。（注：非 -1 情况下，在倒推过程中， $x \bmod 3 = 1$ 的情况只会出现 1 次。）

- 在 -1 情况下，$x$ 将无法还原至 1，或在倒推过程中，$x \bmod 3$ 值出现了与非 -1 情况下不同的情况。（如 $x \bmod 3 = 2$，或 $x \bmod 3 = 1$ 出现了 2 次及以上。）

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int f;
long long x, ans;
int main() {
	scanf("%lld", &x);
	for (int i = 30; i >= 1; i--) {
		if (x % 3 == 2)printf("-1"), exit(0);
		else if (x % 3 == 1) {
			if (f)printf("-1"), exit(0);
			ans = i, f = 1, x--;
		}
		x /= 3;
	}
	if (x == 1)printf("%lld", ans);
	else printf("-1");
	return 0;
}
```

---

## 作者：CleverRaccoon (赞：0)

## 题目

[题目传送门](https://www.luogu.com.cn/problem/AT_past202107_e)

## 思路

我们来观察一下这个数字的变化（假设 $k = 4$，只列举前 $5$ 项）：

| 第 $i$ 次操作 | 可能被改变的数字 | 最终数字 |
| -----------: | -----------: | -----------: |
| $1$ | $1$ | $1$ |
| $2$ | $3$ | $3$ |
| $3$ | $9$ | $9$ |
| $4$ | $27$ | $28$ |
| $5$ | $84$ | $84$ |

从中可以发现，$28$ 和 $84$ 模 $3$ 余 $1$，$1$、$3$ 和 $9$ 模 $3$ 余 $0$。也就是说，在第 $k+1$ 次操作时，如果最终数字为 $w$，那么第 $k$ 次操作时的最终数字为 $w \div 3$，第 $k - 1$ 次操作时的最终数字为 $(w \div 3 - 1) \div 3$。

通过我们的发现，可以得出这样的一个思路：

重复执行 $30$ 次，循环变量 $i$ 从 $30$ 到 $1$ 依次递减。每次循环将 $x$ 除以 $3$，如果当前的 $x$ 模 $3$ 余 $1$，那么将答案设为当前的 $i$。循环结束后，如果它是 $1$，那么输出答案即可，否则，就输出无解。

## 细节

在实现的过程中，还有三点细节需要注意：

1. 循环中，因为青木君只会在一次操作后，将 $x$ **加一**，所以如果当前的 $x$ 模 $3$ 余 $2$，那么可以直接判定无解。

2. 循环中，因为青木君只会在**一次**操作后，将 $x$ 加一，所以如果有两次 $x$ 模 $3$ 余 $1$，也可以直接判定无解。这里可以使用一个标记变量来记录之前是否出现过 $x$ 模 $3$ 余 $1$ 的情况，如果第二次出现，就是无解的情况。

3. 因为 $1 \leq n \leq 10^{15}$，所以要开 `long long`！

## 代码

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ll x;
    cin >> x;
    bool flag = false;
    int ans = -1;
    // x每次除以3，还原乘的过程。
    for(int i = 30; i >= 1; --i, x /= 3) {
        if(x % 3 == 2) {    // 除以3余2不满足条件
            puts("-1");
            return 0;
        }
        if(x % 3 == 1) {    // 除以3余1
            if(flag) {  // 如果之前有过除以3余1那么不满足条件
                puts("-1");
                return 0;
            }
            ans = i;    // 更新答案
            --x;    // x减去那个多乘的1
            flag = true;    // 记录一下，出现过除以3余1的情况
        }
    }
    // 只有除完以后x只剩下1时输出答案，否则不满足条件
    printf("%d", x == 1ll ? ans : -1);
    return 0;
}
```

谢谢大家！完结撒花！


---

