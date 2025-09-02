# Unique Number

## 题目描述

You are given a positive number $ x $ . Find the smallest positive integer number that has the sum of digits equal to $ x $ and all digits are distinct (unique).

## 样例 #1

### 输入

```
4
1
5
15
50```

### 输出

```
1
5
69
-1```

# 题解

## 作者：asasas (赞：5)

这题其实运用了**贪心**思想。

题目中求得是数最小，所以我们要将答案的位数尽可能小，并将大的数往低位填，直到填不下去为止。

注意：

①：由于只能用$0$~$9$之间的数，所以当$n>45$时无解，输出-1即可。

②：由于$0$对整个数位数之和没有影响，而且会使这个数位数增多，所以我们完全不用考虑$0$。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
bool uss[15];//数字桶
int main(){
    int t;
    cin >> t;
    while(t--){
    	int n;
    	cin >> n;
    	memset(uss,0,sizeof(uss));//清空桶
    	if (n>45){
    		cout << -1 << endl;//n>45时直接输出无解
    		continue ;
    	}
    	int ans=0;
    		for (register int i=9;i>=1;i--){
    			if (uss[i]==0&&n>=i){
    				uss[i]=1;
    				ans=ans*10+i;
    				n-=i;//能填就填
    			}
    			if (n==0) break;//填完了就退出
    	}
    	int num=0;
    	while(ans){
    		num=num*10+ans%10;//由于之前求的是答案数的倒序，所以最后要将它还原一下，还原成正序
		ans/=10; 
    	}
    	cout << num << endl;//输出
    }
    return 0;
}

```


---

## 作者：张语诚ZYC (赞：3)

# 该贪心就贪心
## [题目](https://www.luogu.com.cn/problem/CF1462C)回顾
构造一个正整数满足:

1. 这个正整数的各位之和等于 $x$.
2. 这个正整数的每一位数字都不一样.
3. 在满足前两个条件的情况下,这个正整数是最小的那个.

## 思路分析
楼下有神仙 dfs 暴力出奇迹，但是我们是要注重效率得人，~~**该贪心就贪心**~~，~~**省时省力**~~。

通过读题，我们发现，（~~敲黑板~~）：

1. 这个数字不超过9位（很显然，答案中不能有0，所以不考虑0）。
2. 如果 $x > 45$ ，那么无解，因为 $1+2+3+4+5+6+7+8+9=45$ 若要同时满足每一位数字都不一样是不现实的。

于是开开心心的写代码就行了！当然，对于本题，可以为了效率，采取打表大法（后附）。

## $\texttt{AC Code}$：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read_int(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			w=-1;
		} 
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		s=s*10+ch-'0';ch=getchar();
	}
	return s*w;
}
int core(int input){
	int ans=0,tmp=10;
	if(input>45){
		return -1;
	}
	for(int i=9;input-i>0;i-=1){
		input-=i;
		tmp=i;
	}
	if(input>0){
		ans+=input;
	}
	for(int i=tmp;i<=9;i++){
		ans*=10;
		ans+=i;
	}
	return ans;
} 
int main(){
	int t=read_int();
	for(int i=1;i<=t;i+=1){
		int x=read_int();
		printf("%d\n",core(x));
	}
	return 0;
} 
```
## 打表：

```cpp
#include<bits/stdc++.h>
using namespace std;
int data[46]={0xffffffff,1,2,3,4,5,6,7,8,9,19,29,39,49,59,69,79,89,189,289,389,489,589,689,789,1789,2789,3789,4789,5789,6789,16789,26789,36789,46789,56789,156789,256789,356789,456789,1456789,2456789,3456789,13456789,23456789,123456789};
inline int read_int(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			w=-1;
		} 
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		s=s*10+ch-'0';ch=getchar();
	}
	return s*w;
}
int main(){
	int t=read_int();
	for(int i=1;i<=t;i+=1){
		int x=read_int();
		if(x>45){
			puts("-1");
		}else{
			printf("%d\n",data[x]);
		}
	}
	return 0;
} 
```
关于这个表的来源，只需要简简单单改改就行了，例如：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read_int(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			w=-1;
		} 
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		s=s*10+ch-'0';ch=getchar();
	}
	return s*w;
}
int core(int input){
	int ans=0,tmp=10;
	if(input>45){
		return -1;
	}
	for(int i=9;input-i>0;i-=1){
		input-=i;
		tmp=i;
	}
	if(input>0){
		ans+=input;
	}
	for(int i=tmp;i<=9;i++){
		ans*=10;
		ans+=i;
	}
	return ans;
} 
int main(){
	freopen("data.txt","w",stdout);
	int t=45;
	for(int i=1;i<=t;i+=1){
		int x=i;
		printf("%d,",core(x));
	}
	return 0;
} 
```

---

## 作者：EuphoricStar (赞：2)

首先我们发现，如果 $x > 45$ 是无解的，遇到这种情况直接输出 $-1$。

其次就是贪心。定义字符串 $res$ 存储结果。从 $9$ 到 $1$ 枚举每一个数，如果 $x$ 小于当前数位的数则跳过。之后将这个数添加到 res 的开头，如果 $x$ 刚好等于 $0$ 说明数字构造完毕，退出循环。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

int t, x;

int main()
{
    ios::sync_with_stdio(0);
    cin >> t;
    while (t--)
    {
        cin >> x;
        if (x > 45) cout << -1 << endl;
        else
        {
            string res = "";
            for (int i = 9;; --i)
            {
                if (x < i) continue;
                x -= i;
                res = char(i + '0') + res;
                if (!x) break;
            }
            cout << res << endl;
        }
    }
    return 0;
}
```


---

## 作者：_OJF_ (赞：2)

这道题也算是比较水的，先判断能否造出，再判断最小位数，最后再贪心一下即可

但是$"(1 \le x \le 50)"$，并且没有其他东西，这告诉我们什么？可以打表，并且容易打表！找着规律的话，手敲也是很好做的

直接上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, x, a[51] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 19, 29, 39, 49, 59, 69, 79, 89, 189, 289, 389, 489, 589, 689, 789, 1789, 2789, 3789, 4789, 5789, 6789, 16789, 26789, 36789, 46789, 56789, 156789, 256789, 356789, 456789, 1456789, 2456789, 3456789, 13456789, 23456789, 123456789, -1, -1, -1, -1, -1}; 
int main(){
	cin>>t;
	while(t--){
		cin>>x;
		cout<<a[x]<<endl;
	}
	return 0;
}
```


---

## 作者：UperFicial (赞：1)

# 暴力出奇迹

### 前言

楼下神仙都用贪心，$dfs$ 党站了起来。

> 万物皆可搜。

题目链接：[$\text{Link}$](https://www.luogu.com.cn/problem/CF1462C)

### 题意简述

给定一个正整数 $x$，要求构造一个正整数 $y$，使得：

- $y$ 的各个位上的数字之和等于 $x$。

- $y$ 的每一位上的数字不一样。

- $y$ 在可能情况下最小。

### 题目分析

一眼看到 $x\le 50$ 的数据，爆搜无疑。

$dfs$ 两个参数，$now$ 和 $sum$，分别表示目前构造的这个数和它各个位上的数字之和。

根据题意，$now$ 的各个位上的数字之和需要等于 $x$，所以得出终止条件 $sum$ 等于 $x$ 的时候。

由于 $y$ 需要最小，就把目前构造的这个数 $now$ 与我们最终答案 $ans$ 之间取个 $\min$，而 $ans$ 一开始需要赋成无穷大。

下一步，我们可以让 $now$ 的后面再加个数，前提这个数在 $now$ 之中没有出现过。设我们加上的这个数为 $r$，则 $now$ 就变为 $now*10+r$，$sum$ 变为 $sum+r$，而 $r$ 则是我们需要去枚举的一个个位数。

对于出没出现过，可以额外设一个 $use$ 数组来标记一个数有没有出现过，故需回溯。

但这样一个暴力可能很悬，需要加上两个剪枝：

- 可行性剪枝：如果目前的 $sum$ 已经比 $x$ 大，那么往后不管加多少个数都不可能等于 $x$，要及时 $\text{return}$。

- 最优化剪枝：如果目前的 $now$ 已经大于已知答案 $ans$，那么不管再加多少个数只可能比答案还要大，也需及时 $\text{return}$。

[$code$](https://paste.ubuntu.com/p/ssm44jQKGF/)

[$AC$ 记录](https://www.luogu.com.cn/record/44190610)

$$\texttt{The End.by UF}$$

---

## 作者：信守天下 (赞：0)

## [CF传送门](https://codeforces.ml/contest/1462/problem/C)
## [洛谷传送门](https://www.luogu.com.cn/problem/CF1462C)
## 思路:贪心

因为要使解最小,又要满足每位数字不一样

决定大小的因素有两个,1是数字数量,2是数字大小

数量越多,数字肯定越大

所以我们要从$9$开始贪心,来保证数字的数量是最少的

因为总和一定,先取数字越大,后面取的数就越小

## 证明贪心策略如下

因为总和$x$一定

设贪到数为$a_1$,$a_2$,$a_3$...

其中$a_1$为最大数,$n$为贪到的个数

如果有比从大数开始贪心起更优的方案

1,因为从大数贪起,$n$肯定是最小的

所以数字数上不可能更优

2,因为总和一致,所有的数之和都为$x$

所以$a_1$越大,$a_2$,$a_3$...就越小

所以在构成的数字上,从大数贪的的$\overline{a_na_{n-1}...a_1}$肯定小于别的方案

# $code$
~~~cpp
#include <iostream>
using namespace std;
int n;
int A () {
  int m;
  cin >> m;                         //读入
  if (m > 45) {                     //1加到9一共只有45,大于45无解
    return -1;
  }
  int sum = 0 , k = 1;              //sum是数,k是当前位数
  for (int i = 9; i > 0; i--) {
    if (m - i >= 0) {               //能贪
      sum += k * i, k *= 10, m -= i;//贪进去,m减少,当前位数增高1位
    }
  }
  return sum;                       //返回构造的数
}
int main() {
  cin >> n;                         //读入数据总数
  while (n--) {                     //多组数据
    cout << A() << endl;
  }
  return 0;                         //结束
}
~~~

---

## 作者：Griseo_nya (赞：0)

这道题的题目很明显的告诉了我们要贪心
。
首先，题目要求我们“找出符合条件的最小数”，而这道题中各个数位填什么对下一位填的数几乎没有关系（除了你不能再用这个数），故知道我们可以用贪心的方法来解决这道题。

那么下面就该想：怎么贪心呢？

明显在 $x<10$ 时直接输出 $x$ 就可以，因为多位明显是会比一位的数大的。

因为题目要求我们各位数字不能重复，所以我们能取到的最大的 $x$ 就是 $0+1+2+3+4+5+6+7+8+9=45 $ 所以当 $x>45$ 时就无法取到，直接输出 $-1$ 即可。

其余的数我们可以用贪心的思路（前面说过了我们要这样啊）：

从大往小，依次从大往小填数，每次给 $x$ 减去本位要填的数，当本位应填的数大于 $x$ 时，就停止循环，并且输出每一位就ok啦☆

那么下面就是代码啦：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
int main(){
	cin>>t;
	while(t--){
		int x;
		cin>>x;
		if(x<10)cout<<x<<endl;              //预处理 x<10 的情况
		else if(x>45)cout<<-1<<endl;        //预处理 x>45 的情况
		else{
			int i;
			vector<int> a;                  //开一个 vector ，可以理解为动态数组
			for(i=1;i<=9;i++){
				int now=10-i;               //当前应填的数字
				if(now>=x){
					cout<<x;   
					//x 即是我们当前应填的最高位，所以可以直接输出
					reverse(a.begin(),a.end()); 
					//因为我们是从后往前填的，所以要反转一下
					for(int i=0;i<a.size();i++){
						cout<<a[i];         //输出之前的每位数字
					}
					cout<<endl;             //换行
					break;                  //本次循环结束
				}
				else {
					x-=now;                 //给剩余的 x 减去当位应填的数
					a.push_back(now);       //把这位数放进数组里
				}
			}
		}
		
	}
	return 0;
}
```
        

---

## 作者：WanderingTrader (赞：0)

简单思维题
### 题目分析
由于要满足条件的最小数，因此数字的位数要尽量小。

所以数字的低位要尽量大。

因为每一位数字都不一样，所以从个位开始往高位依次填 $9,8,7,\dots$ ，直到剩余数字不够了为止。

由此可见，当 $x>\sum_{i=1}^9i=45$ 时，无解。

### 代码
直接模拟即可
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[20],T,x,u,i;
int main()
{
	scanf("%d",&T);
	for(;T;--T)
	{
		scanf("%d",&x);
		if(x>45) {puts("-1");continue;}
		u=9; i=0;
		while(x>0)
		{
			a[++i]=min(x,u);
			x-=u;
			--u;
		}
		for(int k=i;k;--k) printf("%d",a[k]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：PLDIS (赞：0)

## 解法：
这道题比较水，首先我们得特判：**只要给出的总和大于 $45$，那么肯定无解，因为 $1$ 加到 $9$ 只有 $45$，即使 $1$ 到 $9$ 全上，各个数位加起来也只有 $45$。** 毕竟每个数位都得不同。

然后，我们就可以从 $9$ 开始枚举数位，因为我们要让它**的数位最小**，所以要从最大的数字开始向下枚举。我们可以使总和减去这个数，再用数组存各个数位上的数。

## 注意点：
- 注意**各个数位互不相同**，所以要递减，不能直接全减 $9$。
- 注意要**最小**，要倒序输出。
- 在倒序输出数位之前，得先输出减了这些数后**剩下的和**，因为总和有可能不会让你很整地减掉，会剩下来一个比较小的数，为了让输出的数**最小**，得让这个剩下来的数**最先输出**。

# Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
const int EG = 45; //最大值
int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        //特判
        if(n > EG){
            cout << -1 << endl;
            continue;
        }
        int ans[13] = {0};
        int temp = 1;
        //开始减
        while(1){
            if(n - 9 + temp - 1 < 0){
                break;
            }
            ans[temp] = 9 - temp + 1; //存数
            n -= 9 - temp + 1; //减掉这个数
            temp++;
            if(n == 0){
                break;
            }
        }
        //没有正好减到0
        if(n != 0){
            cout << n;
        }
        //倒序输出
        for(int i = temp - 1;i > 0;i--){
            cout << ans[i];
        }
        //注意换行
        cout << endl;
    }
    return 0;
}
```

---

## 作者：Natsume_Rin (赞：0)

其实这一题就是贪心。

- 首先，发现，只要 $x>45$，就可以直接输出 $-1$。
- 构造的数中有 $0$ 一定不是最优的。

为了使构造出来的数最小，先要使它的位数最少。于是，就有了下面的代码。

```cpp
#include<bits/stdc++.h>
#define RI register int
using namespace std;
int t;
int x;
int las;
int p;
int tot;
int b[1111];
int main(){
        cin>>t;
        while(t--){
                cin>>x;
                tot=0;
                if(x>45) cout<<-1<<endl;
                else{
                        for(RI i=9;i>=1;i--){
                                if(x<i) continue;
                                x-=i;
                                b[++tot]=i;
                        }
                        for(RI i=tot;i>=1;--i) cout<<b[i];
                        cout<<endl;
                }
        }
}   

---

