# Base -2

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=23&page=show_problem&problem=2062

[PDF](https://uva.onlinejudge.org/external/111/p11121.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11121/fa7bc9d210580e6415e9107212fb15b89e8de60a.png)

## 样例 #1

### 输入

```
4
1
7
-2
0```

### 输出

```
Case #1: 1
Case #2: 11011
Case #3: 10
Case #4: 0```

# 题解

## 作者：Fcersoka (赞：6)

~~这道题怎么跟[AT4239](https://www.luogu.com.cn/problem/AT4239)很像 ？~~  
这是一道蓝题 ，这意味着它并不简单 。  
题目翻译在讨论区里有 ，当然 ，你也可以在我的题解里看 。   
先说一下题目翻译 ，题目大概意思是 ：先给出一个整数 $n$，再给出 $n$ 个十进制整数 ，求这 $n$ 个十进制整数的 $-2$ 进制 。  
这道题没什么好说的 ，直接用短除法 ，对 $-2$ 取余 ，由于这个余数可能是负数 ，所以需要求它的绝对值 ，用 abs 即可 ，再用一个数组存储 ，最后再减去余数 ，除以 $-2$。最后，再倒着输出就行了 。这里有个值得注意的的地方 ，就是当给出的十进制整数为 $0$ 时 ，它 $-2$ 进制也为 $0$ ，所以需要进行特判 。  
AC 代码如下 。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[1000001],t;
int main() {
	cin>>t;
	for(int j=1;j<=t;j++) {
		memset(a,0,sizeof(a));
		long long ans=0;
		cin>>n;
		cout<<"Case #"<<j<<": ";
		if(n==0){
			cout<<0<<endl;
			continue;
		}
		while(n){
			a[++ans]=abs(n%(-2));
			n=(n-a[ans])/(-2);
		}
		for(int i=ans;i>0;i--)
		cout<<a[i];
		cout<<endl;
	}
	return 0;
}
```
最后 ，感谢您的观看 ！

---

## 作者：StudyingFather (赞：3)

其实是一道水题。（[ABC105C](https://beta.atcoder.jp/contests/abc105/tasks/abc105_c)是一道一模一样的题）

------------

虽然是负进制数，但我们还是可以采用短除法。

但是要注意C++中除号和MOD的feature，除法是向0取整的，所以 $ (-9)/(-2)=4 $ ，根据余数的定义，可以得出 $ (-9) \mod (-2) = (-9)-4 \times (-2) =-1 $.（负负得负？）

然后就简单了。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[35],cnt;
int main()
{
 int n,kase=0;
 scanf("%d",&n);
 while(n--)
 {
  int num;
  scanf("%d",&num);
  memset(a,0,sizeof(a));
  cnt=0;
  printf("Case #%d: ",++kase);
  if(num==0)puts("0");
  else
  {
   while(num!=0)
   {
    a[++cnt]=abs(num%2);
    if(num>=0)num/=-2;
    else num=(num-1)/(-2);
   }
   for(int i=cnt;i>=1;i--)
    printf("%d",a[i]);
   puts("");
  }
 }
 return 0;
}
```

---

## 作者：冒泡ioa (赞：3)

安利下[我的博客](http://bubbleioa.top/)QWQ  
先给一个例子（提示）  
如果我们输入-13，就会输出110111  
1\*1 + 1\*-2 + 1\*4 + 0\*-8 +1\*16 + 1\*-32 = -13
## 题目大意
输入t个十进制N(−2,000,000,000≤N≤2,000,000,000)，输出它的−2进制数
# 题解
平常我们很少会涉及到负进制，按照提示所给内容，我们应该很快能想到第一种做法，
第一种想法，我们去枚举每一个负二进制数，对于每一个负二进制数，我们将它转换成十进制数，看看是不是一样。  
代码如下：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n;
long long p[32];

void init(){
    
    p[0]=1;
    for(int i=1;i<=31;i++){
        p[i]=p[i-1]*-2;
    }
}

inline bool jud(int num){
    int res=0,cnt=0;
    while(num){
        if(num&1)res+=p[cnt];
        ++cnt;
        num>>=1;
    }
    if(res==n)return 1;
    return 0;
}

void out(int num){
    int tmp[200],t=0;
    while(num){
        if(num&1)tmp[++t]=1;
        else tmp[++t]=0;
        num>>=1;
    }
    for(int i=t;i>=1;i--)printf("%d",tmp[i]);
}

int main(){
    init();
    int t;
    cin>>t;
    int T=t;
    while(t--){
        cin>>n;
        printf("Case #%d: ",T-t+1);
        for(long long i=1;i<=1000000000LL;i++){
            if(jud(i)){
                // cout<<"!!"<<i<<endl;
                out(i);
                break;
            }
        }
        cout<<endl;
    }
    return 0;
}
```
然而上面的做法会T，那么我们能不能直接从十进制算到负二进制呢？  
这个需要好好观察一下提示，  
我们发现如果要确定当前位是0还是1，只要对下一个为1时取余就知道了，如果余数为0，那么当前这个数自然是后面位的倍数了，取0，否则就取1.

然后减去当前还剩的数，继续往后走。

最后减到0就可以了。
## 代码
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int MAXN=1e5+7;
const int inf =1e9;
int ans[1000];
long long n;
long long pw(int a,int b){
    long long sum=1;
    long long base=a;
    while(b){
        if(b&1)sum*=base;
        base*=base;
        b>>=1;
    }
    return sum;
}
int main(){
    int t;
    cin>>t;
    int T=t;
    while(t--){
        printf("Case #%d: ",T-t);
        scanf("%lld",&n);
        int top=0;
        if(!n)ans[top++]=0;
        while(n){
            if(n%(pw(-2,top+1)))ans[top]=1;
            else ans[top]=0;
            n-=ans[top]*pw(-2,top);
            top++;
        }
        while(top)printf("%d",ans[--top]);
        printf("\n");
    }
    
    return 0;
}
```

---

## 作者：_cmh (赞：2)

[原题传送门](https://www.luogu.com.cn/problem/UVA11121)

[双倍经验](https://www.luogu.com.cn/problem/AT4239)

## $\texttt{Description}$

给出一个整数 $n$，输出它在 $-2$ 进制下表示的数。

## $\texttt{Solution}$

本题同 $2$ 进制转换一样，也可以用短除法解决。

注意几个点：

- 短除法时，注意答案需要倒过来输出。此处我用的是 `stack` 来输出。

- 同时，$n\bmod -2$ 有可能为 $-1$，输出时记得转化成 $1$ 输出，此处我用的是 $-1$。

- 注意特殊数据 $n=0$ 时，应特判输出 $0$。

- $n\div 2$ 时记得减去余数后再除，而余数是 $-1$ 时应该化为 $1$。

## $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	scanf("%d",&T);
	for(int i=1;i<=T;i++){
		int x;
		scanf("%d",&x);
		printf("Case #%d: ",i);
		if(x==0)
			puts("0");
		else{
			stack<int>ans;
			while(x){
			    int now=abs(x%(-2));
				ans.push(now);
				x=(x-now)/(-2);
			}
			while(!ans.empty()){
				printf("%d",ans.top());
				ans.pop();
			}
			puts("");
		}
	}
	return 0;
}
```

感谢观看。

---

## 作者：hank0402 (赞：2)

upd：将数字间的空格加上。

upd：添加代码块

又是一道水蓝。

$\text{(-2)}$ 进制还是可以使用短除法解决，注意边界条件 “0” 的判断，当该数为 $0$ 时，直接输出 $0$，并且注意`:`后面有一个空格！（我因为这个调了好久）其他的数组初始化什么的应该不用说了，直接上代码。

**Code**：

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans[10001], now = 0;
long long n;
void solve(int x) { //短除法计算
	memset(ans, 0, sizeof(ans)); //注意初始化
	now = 0;
	scanf("%lld", &n);
	if(n == 0) { //当n为0时直接输出0
		cout << "Case #" << x << ": " << 0 << endl; 
		return ;
	}
	while(n) { //短除法
		ans[++now] = n % (-2); //将答案存到ans数组里
		n /= (-2);
		if(ans[now] == (-1)) { ans[now] = 1; n ++;}
	}
	cout << "Case #" << x << ": ";
	for(int i = now; i >= 1; i --) cout << ans[i]; //倒序输出
	cout << '\n'; //别忘了换行
	return ;
} 
int main() {
	int T;
	cin >> T;
	for(int i = 1; i <= T; ++i) solve(i);
	return 0;
}
```

---

## 作者：Blikewsr (赞：2)

 - [$\color{lightblue}\text{[UVA11121 原题连接]}$](https://www.luogu.com.cn/problem/UVA11121)
 
 - 题目描述     
   给出一些整数 `N` ， 满足 $ -10^9 ≤ N ≤ 10^9 $ ，请计算出其 `-2` 进制表示的数。       
 
 - 输入格式                           
   一些十进制数 `N` ， 满足 $ -10^9 ≤ N ≤ 10^9 $ 。            
 
 - 输出格式    
   `N` 的 `-2` 进制的数。               
 
 - 思路  
   我们可以利用小学学过的短除法来做， 但是要注意的是要倒序输出。
   
   先来看一下二进制怎么求？
   
   ![](https://cdn.luogu.com.cn/upload/image_hosting/dohkudwm.png)
   
   根据上面的图片， 把一个十进制整数转 `2` 的代码就是：
   ```cpp
   while(n) {
       ans[++ top] = n % 2;
       n = (n - ans[top]) / 2;
   }
   ```
   
   自然而然地， 把一个十进制整数转 `-2` 的代码就是：
   ```cpp
   while(n) {
       ans[++ top] = n % (-2);
       n = (n - ans[top]) / (-2);
   }
   ```
   但是， 我们发现， 进制数是一个非负数。
   
   所以， 我们只用在 `n` `%` `(-2)` 这里再加一个绝对值就行了。 
   
   该部分代码：
   ```cpp
   while(n) {
       ans[++ top] = abs(n % (-2));
       n = (n - ans[top]) / (-2);
   }
   ```
   最后， 在输出时只用倒叙输出就行了。
   
   注意： 当 `N = 0` 时， 直接输出 `0` 。                         
   
 - 代码实现              
 ```cpp
#include <bits/stdc++.h>
#define int long long
#define N 99999999
using namespace std;
int n, x, num, a[N];
int abs_math(int y) {      // 绝对值函数
	if(y < 0) return (- y);
	return y;	
}
signed main() {
	cin >> n;
	while(n) {
		n --;
		num ++;
		cin >> x;
		cout << "Case #" << num << ": ";
		if(x == 0) {
			cout << 0 << '\n';
			continue;
		}
		int top = 0;
		while(x) {
			a[++ top] = abs_math(x % (- 2));
			x = (x - a[top]) / (- 2);
		}
		for(int i = top; i >= 1; i--) {
			cout << a[i];	
		}
		cout << '\n';
	}
	return 0;	
}
 ```

 - 此题解仅供参考， 感谢 ！

---

