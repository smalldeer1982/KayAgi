# Bear and Finding Criminals

## 题目描述

There are $ n $ cities in Bearland, numbered $ 1 $ through $ n $ . Cities are arranged in one long row. The distance between cities $ i $ and $ j $ is equal to $ |i-j| $ .

Limak is a police officer. He lives in a city $ a $ . His job is to catch criminals. It's hard because he doesn't know in which cities criminals are. Though, he knows that there is at most one criminal in each city.

Limak is going to use a BCD (Bear Criminal Detector). The BCD will tell Limak how many criminals there are for every distance from a city $ a $ . After that, Limak can catch a criminal in each city for which he is sure that there must be a criminal.

You know in which cities criminals are. Count the number of criminals Limak will catch, after he uses the BCD.

## 说明/提示

In the first sample, there are six cities and Limak lives in the third one (blue arrow below). Criminals are in cities marked red.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF680B/53b34f04c80c68b5459bb6787b79d861ce7bb49e.png)Using the BCD gives Limak the following information:

- There is one criminal at distance $ 0 $ from the third city — Limak is sure that this criminal is exactly in the third city.
- There is one criminal at distance $ 1 $ from the third city — Limak doesn't know if a criminal is in the second or fourth city.
- There are two criminals at distance $ 2 $ from the third city — Limak is sure that there is one criminal in the first city and one in the fifth city.
- There are zero criminals for every greater distance.

So, Limak will catch criminals in cities $ 1 $ , $ 3 $ and $ 5 $ , that is $ 3 $ criminals in total.

In the second sample (drawing below), the BCD gives Limak the information that there is one criminal at distance $ 2 $ from Limak's city. There is only one city at distance $ 2 $ so Limak is sure where a criminal is.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF680B/9b09abcaba16810167119bac2c883bc8bf99b11b.png)

## 样例 #1

### 输入

```
6 3
1 1 1 0 1 0
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 2
0 0 0 1 0
```

### 输出

```
1
```

# 题解

## 作者：Wendy_Hello_qwq (赞：9)

[题目传送门。](https://www.luogu.com.cn/problem/CF680B)

## 题目大意

给定城市数量 $n$ ，给定当前城市 $a$ ，给定 $n$ 个城市。

想知道从 $a$ 城市距离 $i$ 的城市能不能确切抓捕罪犯。

## 主体思路

- 距离 $a$ 城市 $i$ 的城市无非就两个：$a+i$ 和 $a-i$ 城市。

- 只要两个城市中有一个城市没有罪犯，就不能确定抓捕。

## 上代码

```cpp
#include <cstdio>
using namespace std;
int n, a, num, b[107];
int main()
{
	scanf ("%d%d", &n, &a);
	for (int i = 1; i <= n; i++)
	{
		scanf ("%d", &b[i]);
		// 一边输入一边判断有几个罪犯
		if (b[i] == 1)
			num++; 
	}
	// 距离a城市i距离的有两个城市：a+i和a-i，判断是否出界 
	for (int i = 0; a + i <= n && a - i >= 1; i++)
	{
		// 只要这两个城市中有一个没有罪犯，就不能确定，减掉抓捕罪犯数 
		if (b[a + i] + b[a - i] == 1)
			num--;
	}
	printf ("%d", num);
	return 0;
}
```

完结撒花！

---

## 作者：adminnew (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF680B)

## 题目大意
给定城市数量 $n$ ，给定当前城市 $a$ ，给定 $n$ 个城市。想知道从 $a$ 城市距离 $i$ 的城市能不能确切抓捕罪犯。(来源： Wendy_Hello 的题解)
## 思路

题目告诉了警察和囚犯的距离。所以，如果两个城市都有囚犯，那么肯定可以抓到；但是，如果有一个城市没有罪犯的话，那么我们不能确定有没有囚犯，则没办法抓到。

模拟即可 AC 。

### 代码
```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
int n,m,sum;//变量 
int a[100024];
int main()
{

    cin>>n>>m;
    for(int i=1;i<=n;i++)
	{
        cin>>a[i];
        if(a[i]) sum++;//判断 
    }
    for(int i=1;m+i<=n&&m-i>=1;i++)//判断*2
        if(a[m-i]+a[m+i]==1) sum--;
    cout<<sum;
    return 0;
}
```

---

## 作者：mc_xiexie (赞：1)

# CF680B Bear and Finding Criminals
## 思路
1. 定义一个 `bool` 数组，因为每个城市最多只能有一个罪犯。所以输入进数组里，如果有罪犯就为真，无罪犯就为假。
```
for(int i=1;i<=n;i++){
	cin>>b[i];
}
```
2. `for` 遍历数组，如果 `a-i<1&&a+i>n` 就退出循环。 `for(int i=0;a-i>=1||a+i<=n;i++)`。
3. 如果 `a+i==a-i` 就只用判断 `b[a]` 是否为真，为真 `ans++`。
```
if(a+i==a-i){
   if(b[a]){
		ans++;
	}
}
```
4. 如果 `a+i<=n && a-i>=1` 即均在范围之内，判断 `b[a+i] && b[a-i]` 是否为真，为真 `ans+=2`，因为能抓两个罪犯。
```
else if(a+i<=n && a-i>=1){
	if(b[a+i] && b[a-i]){
		ans+=2;
	}
}
```
5. 如果 `a+i<=n && a-i<1` 即左不在范围之内，判断 `b[a+i]` 是否为真，为真 `ans++`。
```
else if(a+i<=n && a-i<1){
	if(b[a+i]){
		ans++;
	}
}
```
6. 如果 `a+i>n && a-i>=1` 即右不在范围之内，判断 `b[a-i]` 是否为真，为真 `ans++`。
```
else if(a+i>n && a-i>=1){
	if(b[a-i]){
		ans++;
	}
}
```
## 完整代码

```
#include<bits/stdc++.h>
using namespace std;
bool b[105];
int main(){
	int a,n,ans=0;
	cin>>n>>a;
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	for(int i=0;a-i>=1||a+i<=n;i++){
        if(a+i==a-i){
            if(b[a]){
                ans++;
            }
        }
		else if(a+i<=n && a-i>=1){
			if(b[a+i] && b[a-i]){
			    ans+=2;
			}
		}
		else if(a+i<=n && a-i<1){
			if(b[a+i]){
			    ans++;
			}
		}
		else if(a+i>n && a-i>=1){
			if(b[a-i]){
			    ans++;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：_byta (赞：1)

看到题解这么少，我来发一篇。

首先若存在两个点，分别为 1 和 0 的地点，那很显然，警察不能判断罪犯再那个

位置。所以我们只要特判两个都为 1 的点对就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100002;
int n,m,k,t,p,q,ans,sum,tot,cnt,a[N],b[N];
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	while(1)
	{
		if(k-t<=0&&k+t>n)break;
		if(k-t>=1&&k+t<=n)
		{
			if(a[k-t]==1&&a[k+t]==1) 
			{
				if(t==0)ans++;
			    else ans=ans+2;
		    }
		}
		if(k-t<=0&&a[k+t]==1)ans++;
		if(k-t>=1&&k+t>n&&a[k-t]==1)ans++;
		t++;
	}
	cout<<ans<<endl;
}
```




---

## 作者：__DayLight__ (赞：0)

## 前言
貌似现有题解几乎都是围绕着 $a+i$ 与 $a-i$ 进行处理，那我就写个双指针吧。

## 思路
先了解简化题意：
>给出长度为 $n$ 的 $01$ 序列，给出指定的一个数的位置 $a$，如果距离数 $a$ 的长度相同的两个数都是 $1$，那么就将这 $2$ 个数称为**真数**，求该序列中共有多少个**真数**。

所以，我定义两个指针 $L$ 与 $R$ 分别指向距离数 $a$ 的长度相同的两个数，让它们按同样的速度向左、右移动，以此判断**真数**。

可是数 $a$ 不一定是序列中的中心啊，万一其中一个指针率先到达列首或列尾怎么办？

在这种情况下，我们就可以让率先到达列首或列尾的指针**停止移动**，剩下的指针继续移动，如指向了 $1$，就直接将这个数视为**真数**，因为它**没有**距离数 $a$ 的长度相同的数了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,ans;
bool t[105];
signed main(){
    cin>>n>>a;
    for(int i=1; i<=n; i++)
    	cin>>t[i];
    for(int L=a+1,R=a-1;;)
    {
    	//如果指针未到达列首或列尾就继续移动。 
    	if(L>1)L--;
    	if(R<n)R++;
    	//两个指针离 a 的距离相等说明都未到达列首或列尾。 
    	if(a-L==R-a)
    	{
    		if(L==R&&t[L])ans++;//L = R 代表都指向数 a，只算作一个真数 
			else ans+=t[L]*t[R]*(t[L]+t[R]);
			//如果这两个数中有一个是 0，那么它们就不是真数，所以乘积自然是 0，反之乘积就是 1 + 1 = 2， 因为这有两个真数。 
    	}
    	if(a-L<R-a)ans+=t[R];//这说明 L 率先到达了列首，只需判断指针 R 指向的数即可。 
    	if(a-L>R-a)ans+=t[L];//这说明 R 率先到达了列尾，只需判断指针 L 指向的数即可。
    	if(L==1&&R==n)break;//都到达了列首和列尾，结束循环。 
    }
    cout<<ans;
	return 0;
}

```

---

## 作者：LookatSea (赞：0)

思路：根据题意可知，如果两个城市都有罪犯，那么一定可以抓到，若有一个城市没有罪犯，则不确定有没有罪犯，无法抓获。**因为关联这个城市的两个点无非是 $c+1$ 和 $c-1$ 其中若一个城市没有罪犯，就无法知道两个城市哪个有罪犯了。**


代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,a,cnt=0;
    cin>>n>>a;
    int t[14250];
    for(int i=1;i<=n;i++){
        cin>>t[i];
        if(t[i]) cnt+=1;
    }
    for(int i=1;a+i<=n&&a-i>=1;i++){
        if(t[a+i]+t[a-i]==1){
            cnt--;
        }
    }
    cout<<cnt;
}
```

---

## 作者：OJ_killer (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/solution/CF680B)

题目意思非常明确：就是红指定从哪个开始，BCD会依次告诉指定的距离为 $0、1、2\dots$ 的罪犯数量，然后我们就想哪个城市有罪犯，问最多能抓到多少？

### 那么问题来了：

如何知道该城市有没有罪犯呢？

其实不难发现会出现三种情况：

+ 1.距离 $i$ 为 $0$ 时 $a+i$ 就是位置 $a$ 的罪犯数量。

+ 2.$a+i$ 或 $a-i$ 不存在时，我们就进行判断 $a+i$ 或 $a-i$ 的罪犯数量，如果为 $1$，那么位置上有罪犯。

+ 3.从 $1$ 开始枚举，判断 $a+i$ 和 $a-i$ 的罪犯数，如果是 $2$，说明两边距离为 $i$ 的城市都有罪犯。如果是 $1$，我们就不能知道位置。

详见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n, m, a[105], ans;

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	if (a[m])
		ans++;
	for (int i = 1; ; i++) { //开始枚举
		if (m - i > 0 && m + i <= n) { //情况一
			if (a[m - i] && a[m + i])
				ans += 2;
		} else if (m - i <= 0 && m + i <= n) { //情况二
			if (a[m + i])
				ans++;
		} else if (m - i > 0 && m + i > n) { //情况三
			if (a[m - i])
				ans++;
		}
		else //都不符合跳出
			break;
	}
	cout << ans;
	return 0;
}

---

## 作者：Fish_redflying (赞：0)

令城市 $i$ 为 $City_i$

假设利克马可以用 BCD 检测到所有罪犯，那么每当我们确定不能肯定时，便减少一只。

距离城市 $i$ 为 $a$ 的只有两个，$City_{i-a}$ 和 $City_{i+a}$。所以我们考虑两种情况。

- 两个城市都有，这是必然有罪犯的。

- 两个城市有一个，无法确定在某一个在哪里。

综上思路，即可写出代码。

```python
n,a=map(int,input().split())
li=list(map(int,input().split()))
total=sum(li)
for i in range(min(a-1,n-a)+1) : total-=li[a-i-1]^li[i+a-1]
print(total)

```

希望对大家有帮助。

---

## 作者：wangzc2012 (赞：0)

# CF680B Bear and Finding Criminals
## 题目大意
给出城市数量 $n$，警察所在城市 $a$ ，和每个城市的罪犯数量 $t _ {i}$ 。求如果已知离 $a$ 市一定距离内的罪犯数量，有多少城市一定有罪犯。
## 思路分析
与 $a$ 市距离为 $i$ 的城市有两个，分别为 $a+i$ 和 $a-i$。    
我们分两种情况讨论：
1. 如果两个城市都有罪犯，那么一定可以将其抓获。
2. 如果两个城市中有一个城市没有罪犯，那么就无法确定罪犯到底在哪个城市里，无法抓获罪犯。

所以，我们只需要先求出罪犯总数，再减去第二种情况的罪犯数量即可求出答案。
## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,lt[105],ans;
int main(){
    cin>>n>>a;
    for (int i=1;i<=n;i++){
        cin>>lt[i];
        ans+=lt[i];
    }
    for (int i=0;a-i>=1 and i+a<=n;i++){
        if (lt[i+a]+lt[a-i]==1) ans--;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Tjl0427 (赞：0)

# 题解：CF680B Bear and Finding Criminals
[题目传送门。](https://www.luogu.com.cn/problem/CF680B)
### 思路：
因为每个城市最多只能有一个罪犯，所以直接定义一个 `bool` 类型的数组，如果这个城市里有罪犯就为真，否则为否。
```c
for(int i=1;i<=n;i++)
{
  cin>>f[i];
}
```
可以一边输入一边判断是否有罪犯，之后再减去，所以上文代码可改为：
```c
for(int i=1;i<=n;i++)
{
    cin>>f[i];
    if(f[i])
    {
        ans++;
    }
}
```
因为离 $a$ 城距离为 $i$ 的城市有两个：$a + i$ 城和 $a - i$ 城。  
两种情况：
- 这两个城市都是合法的且都有罪犯：可以确定位置。
- 这两个城市中有一个不合法：另一个城市有罪犯的话可以确定。

因为上面已经把所有有罪犯的城市都加上去了，所以现在只需要减去不能确定的就行了：
```c
for(int i=0;a+i<=n&&a-i>=1;i++)
{
	if(f[a-i]+f[a+i]==1)
	{
		ans--;
	}
}
```
最后 `cout` 就行了。

**完整代码只需综合过程。**

---

## 作者：ny_Dacong (赞：0)

# 思路

我们枚举距离。

离 $a$ 城距离为 $i$ 的城市是 $a+i$ 城与 $a-i$ 城。

* 如果 $a+i$ 和 $a-i$ 都是合法的，且两个城市都有罪犯，那么罪犯的位置就可以确定。

* 如果 $a+i$ 和 $a-i$ 之中有一个不合法，那么另外一个城市有罪犯的话他的位置也可以确定。

# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,ans = 0;
bool mark[150];
int main(){
    scanf("%d%d",&n,&a);
    for(int i = 1; i <= n; i++){
        scanf("%d",&mark[i]);
    }
    for(int i = 0; i <= n; i++){
        if(a-i <= 0 && a+i > n){
            break;
        }else if(a-i <= 0 && mark[a+i]){
            ans++;
        }else if(a+i > n && mark[a-i]){
            ans++;
        }else{
            if(mark[a+i] && mark[a-i]){
                ans += 2;
                if(i == 0){
                    ans--;
                }
            }
        }
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 题目描述

[Bear and Finding Criminals](https://www.luogu.com.cn/problem/CF680B)

## 算法思路

看到题目，一下子就想到了**模拟**，枚举 BCD 所探测到的距离，如果搜索到的两端都有罪犯，他就能抓到两人，否则判断不了罪犯在那端。

### 样例讲解

在第一个样例中，有六个城市，Limak 住在第三个城市（下面的蓝色箭头）。罪犯在标有红色的城市里。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF680B/53b34f04c80c68b5459bb6787b79d861ce7bb49e.png)

使用 BCD 为 Limak 提供以下信息：

- 远处有一个罪犯离第三个城市距离为 $0$——Limak 确信这个罪犯就在第三个城市。

- 远处有一个罪犯离第三个城市距离为 $1$——Limak 不知道罪犯是在第二个城市还是第四个城市。

- 远处有两个罪犯离第三个城市距离为 $2$——Limak 确定第一个城市有一个罪犯，第五个城市也有一个。

所以，Limak 会在城市 $1$、$3$、$5$ 里抓罪犯，也就是 $3$ 个罪犯。

时间复杂度：$O(n ^ 2)$。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//日常开long long 
const ll N=110;
ll n,m,a[N],ans;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//输入输出优化 
	cin>>n>>m;
	for(int i=1;i<=n;i++)a 
	{
		cin>>a[i];
	}
	for(int i=0;m-i>=1||m+i<=n;i++)//如果左右端点都在范围外，停止循环 
	{
		if(m-i>=1&&m+i<=n&&a[m-i]&&a[m+i])//如果两个端点都在范围内，而且都有犯罪 
		{
			if(m-i!=m+i)//如果左右端点不是同个点 
			{
				ans+=2;//抓到两个罪犯 
			}
			else//否则 
			{
				ans++;//抓到一个罪犯 
			}
		}
		if(m-i>=1&&m+i>n&&a[m-i])//如果左端点在范围内，而且有犯罪 
		{
			ans++;//抓到一个罪犯 
		}
		if(m+i<=n&&m-i<1&&a[m+i])//如果右端点在范围内，而且有犯罪
		{
			ans++;//抓到一个罪犯
		}
	}
	cout<<ans<<"\n";//输出抓到的犯罪数 
	return 0;
}
```


---

## 作者：123456Mm (赞：0)

本题可以枚举距离。

如果距离$a$的两点其中有一个罪犯，则警察抓不到

否则能抓到
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,n,ans=0;
	cin>>n>>a;
	
	int b[n+1];
	for(int i=1;i<=n;i++){
		cin>>b[i];
		if(b[i]==1)ans++;
	}
	for(int i=0;a+i<=n&&a-i>=1;i++){
		if(b[a+i]+b[a-i]==1){
			ans--;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：HsNu1ly7_ (赞：0)

## 思路

可以先将有罪犯的城市的数量统计出来，再判定如果距离 $a$ 市为 $i$ 的两个城市中只有一个城市有罪犯，那么就不能抓到罪犯。

代码如下：

```cpp
#include <iostream>
using namespace std ;
#define int long long

signed main (){
	ios::sync_with_stdio(0) ;
	cin.tie(0) ;
	cout.tie(0) ;
	int n ;
	int t ;
	cin >> n >> t ;
	int arr[1010];
	int ans = 0 ;
	for ( int i = 1; i <= n;i++ ) cin >> arr[i] ;	

	int l = t , r = t ;
	for ( int i = 1 ; i <= n ;i++ ){
		if ( arr[i] ) ans++ ;
	}

	for ( int i = 1 ; i + t <= n && t - i > 0 ; i++ ){
		if ( arr[i + t] + arr[t - i] - 1 + 1 + 1 - 1 == 1 ) --ans ;
	}
	cout << ans ;
	return 0 ;
}

```

---

## 作者：Laoda_Bryant (赞：0)

## 题意
给你 $n$ 个城市，每个城市用 $0$ 和 $1$ 表示是否有罪犯。问离 $a$ 城市为 $i$ 距离的城市能不能抓捕罪犯。
## 思路
题目中问的是能不能抓捕，其实就是问你能不能确定确定罪犯位置。设每个城市编号为 $k_i$，那么当有罪犯时就有以下几种情况
1. $k_{a-i}$ 和 $k_{a+i}$ 都为 $1$，可以确定位置，因为两个城市都有。
2. $k_{a-i}$ 和 $k_{a+i}$ 一边为 $1$，一边 $0$，不能确定具体在 $k_{a-i}$ 还是 $k_{a+i}$。
3. $k_{a-i}$ 或 $k_{a+i}$ 单独有，另一边超过了边界，可以确定位置。  
  
所以，只要判断一边为 $1$，一边 $0$ 的情况即可。
## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
bool k[105];
int n,a,all=0;
int main(){
	cin>>n>>a;
	for(int i=1;i<=n;i++){
		cin>>k[i];
		if(k[i]) all++;
	}
	for(int i=1;a+i<=n&&a-i>=1;i++){
		if(k[a+i]^k[a-i]) all--;
	}
	cout<<all;
	return 0;
}
```

---

