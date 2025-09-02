# Parliament of Berland

## 题目描述

$Berland$ 有 $n$ 名议员，编号为 $1$ ~ $n$ ，所有编号为奇数的议员都是民主党人，编号为偶数的议员都是共和党人。

新的议会集会厅是一个矩形，由 $a×b$ 把椅子组成——  $a$ 行，每行 $b$ 把椅子。横/纵坐标相差 $1$ 的椅子是相邻的，例如，第 $2$ 行的 $5 $号椅子与该行的 $4$ 和 $6$ 号椅子以及第 $1$ 和 $3$ 行的 $5$ 号椅子相邻。因此，除了大厅边缘的椅子外，每把椅子都与另外 $4$ 把椅子相邻。

如果一个政党的两名议员（即两个民主党人或两个共和党人）在相邻的椅子就座，他们将花费所有时间~~划水~~讨论党内问题。

对于给定的议员人数和大厅大小，确定是否有办法使同一政党的任何两个成员的座位都不相邻。

## 样例 #1

### 输入

```
3 2 2
```

### 输出

```
0 3
1 2
```

## 样例 #2

### 输入

```
8 4 3
```

### 输出

```
7 8 3
0 1 4
6 0 5
0 2 0
```

## 样例 #3

### 输入

```
10 2 2
```

### 输出

```
-1
```

# 题解

## 作者：__Kyw666__ (赞：2)

# 思路分析

* 我们先考虑一下无解情况：  
如果 $n > a × b$ 说明总人数比座位还多，就是无解情况。  
* 再看看枚举：
上面一行如果是先奇后偶，第二行就倒过来，也就是先偶后奇，就能把奇偶性不同的数交替放入。

# 代码实现
```
#include<bits/stdc++.h>
using namespace std;

int mapp[105][105]={0};//存储座位 
int k=1;
int a,b,n;
int main()
{
	cin>>n>>a>>b;
	if(n>a*b)//无解直接输出-1 
	{
		cout<<"-1";
		return 0;
	}
	for(int i=1;i<=a;i++)
	{
		if(i%2==0)//先偶后奇 
		{
			for(int j=1;j<=b;j++)//倒着排，先奇后偶 
			if(k<=n)
			{
				mapp[i][j]=k;
				k++;
			}
		}
		else//先奇后偶  
		{
			for(int j=b;j>=1;j--)//倒着排，先偶后奇
			if(k<=n)
			{
				mapp[i][j]=k;
				k++;
			}
		}
	}		
	for(int i=1;i<=a;i++)//输出座位情况 
	{
		for(int j=1;j<=b;j++)
			cout<<mapp[i][j]<<" ";
		cout<<endl;
	}
	return 0;//完美结束 
}
```
[无注释版](https://www.luogu.com.cn/paste/mnazzykm)

结束！

---

## 作者：XXh0919 (赞：1)

首先我们可以知道：当 $n>a\times b$ 时，无解，直接输出 $-1$ 即可。

然后我们就枚举，把奇偶性不同的数交替放入矩阵，~~避免两个议员划水~~就行了，若有多余的位置就直接往上补 $0$。

### AC Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+13;

int n,a,b;
int t[N][N],cnt=1;

signed main(){
	scanf("%lld %lld %lld",&n,&a,&b);
	if(n>a*b){
		puts("-1");
		return 0;
	}
	for(int i=1;i<=a;++i){
		if(i%2==0){
			for(int j=1;j<=b;++j){
				if(cnt<=n)t[i][j]=cnt++;
				else t[i][j]=0;
			}
		}else{
			for(int j=b;j>=1;--j){
				if(cnt<=n)t[i][j]=cnt++;
				else t[i][j]=0;
			}
		}
	}
	for(int i=1;i<=a;++i){
		for(int j=1;j<=b;++j){
			printf("%lld ",t[i][j]);
		}
		puts("");
	}
    return 0;
}
```


---

## 作者：_Execution_ (赞：1)

## 思路
首先，若人数大于座位总数，即 $n>a \times b$，则绝对不可能坐下，即无解。

再进行枚举，把奇偶性不同的数交替放入，即可。

## 代码

```cpp
#include <iostream>
using namespace std;

int main() {
    int n, a, b;
    cin >> n >> a >> b;

    if (n > a * b) {
        cout << -1 << endl;
        return 0;
    }

    int cnt = 1;
    int ans[101][101];

    for (int i = 1; i <= a; ++i) {
        for (int j = 1; j <= b; ++j) {
            if (cnt <= n) {
                ans[i][j] = cnt++;
            } else {
                ans[i][j] = 0;
            }
        }
    }

    for (int i = 1; i <= a; ++i) {
        for (int j = 1; j <= b; ++j) {
            cout << ans[i][j];
            if(j==b) cout<<endl;
            else cout<<" ";
        }
    }

    return 0;
}

```


---

## 作者：Ninelife_Cat (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF644A)

模拟+构造。

首先如果议员的数量比大厅内座位总数还多，即 $n>a\times b$，那么显然有议员没位置坐，无解。

接下来要保证同一政党的任何两个成员的座位都不相邻，我们只需要让两党的议员交错着坐，即一个偶数上下左右均为奇数，一个奇数上下左右均为偶数，然后多余的位置填 $0$ 即可。

核心代码：

```cpp
int n,a,b,cnt,ans[101][101];//cnt记录当前是第几号议员
signed main()
{
	n=read();a=read();b=read();
	if(n>a*b) return cout<<-1,0;//判无解
	for(ri int i=1;i<=a;++i)
	{
		if(!(i&1)&&!(b&1))//当b是偶数时需一正一反填数才能保证正确性
			for(ri int j=b;j>=1;--j)
				if(cnt>=n) ans[i][j]=0;
					else ans[i][j]=++cnt;
		else for(ri int j=1;j<=b;++j)
			if(cnt>=n) ans[i][j]=0;
				else ans[i][j]=++cnt;
	}
	for(ri int i=1;i<=a;++i)
		for(ri int j=1;j<=b;++j)
			cout<<ans[i][j]<<(j==b?"\n":" ");
	return 0;
}
```

---

## 作者：Laoda_Bryant (赞：0)

[洛谷传送门](https://www.luogu.com.cn/problem/CF644A) | [更好的体验](https://www.luogu.com.cn/article/89jhgajr)  
## 本题题意
有 $n$ 个议员，编号为 $1 \sim n$，就坐在 $a \times b$ 的礼堂里，求如何安排座位能够使得任意两个相邻的座位上的议员奇偶性不相同。
## 思路
### 无解情况
当 $n > a \times b$ 时，必定无法满足，则直接输出 `-1`。
### 有解情况
打表找规律。  
![](https://cdn.luogu.com.cn/upload/image_hosting/oad8fv65.png)     
![](https://cdn.luogu.com.cn/upload/image_hosting/q637s9bx.png)   
我们发现，只要让奇数行正着就坐，偶数行反着就坐，即可安排完全部议员。  
## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,s[105][105],g;
int main(){
	cin>>n>>a>>b;
	if(n>a*b){
		cout<<-1;
		return 0;
	}
	g=1;
	for(int i=1;i<=a;i++){
		if(g>n) break; 
		if(i%2==1){ //正着安排 
			for(int j=1;j<=b;j++){
				if(g>n) break;
				s[i][j]=g;
				g++;
			}
		}else{
			for(int j=b;j>=1;j--){ //反着安排
				if(g>n) break;
				s[i][j]=g;
				g++;
			}
		}
	}
	for(int i=1;i<=a;i++){
		for(int j=1;j<=b;j++){
			cout<<s[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：ny_Dacong (赞：0)

# 思路
奇数与偶数交替着放。模拟即可。

如果 $b$ 是偶数，那么每一行一正一反放。

如果 $b$ 是奇数，那么每一行顺次放。

代码的具体实现方式：奇数行很好办，用两个 `for` 循环直接输出即可。位置不够就补 0。偶数行可以先正着放，然后用栈颠倒顺序。

# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,now = 0;
int main(){
    scanf("%d%d%d",&n,&a,&b);
    if(a*b < n){
        printf("-1");
        return 0;
    }
    if(b%2){
        for(int i = 1; i <= a; i++){
            for(int j = 1; j <= b; j++){
                now++;
                if(now > n){
                    printf("0 ");
                }else{
                    printf("%d ",now);
                }
            }
            printf("\n");
        }
        return 0;
    }
    for(int i = 1; i <= a; i++){
        for(int j = 1; j <= b; j++){
            now++;
            if(now > n){
                printf("0 ");
            }else{
                printf("%d ",now);
            }
        }
        printf("\n");
        i++;
        if(i > a){
            break;
        }
        stack<int> tp;
        for(int j = 1; j <= b; j++){
            now++;
            if(now > n){
                tp.push(0);
            }else{
                tp.push(now);
            }
        }
        while(tp.size()){
            printf("%d ",tp.top());
            tp.pop();
        }
        printf("\n");
    }
    return 0;
}
```

---

## 作者：CodingOIer (赞：0)

## CF644A Parliament of Berland 题解

### 思路分析

一道简单贪心题。

显然，如果 $n > a \times b$ 则无法放下。

否则我们一定有策略放入 $a \times b$ 个人且合法。

- 对于 $b \bmod 2 = 1$，我们一行一行接着放即可。
- 对于 $b \bmod 2 = 0$，我们在奇数行正着放，偶数行反着放即可。

代码实现就交给我们高贵的「三目运算符」实现即可。

### 代码实现

```cpp
#include <cstdio>
constexpr int MaxN = 1e4 + 5;
int n, a, b;
int main()
{
    scanf("%d%d%d", &n, &a, &b);
    if (n > a * b)
    {
        printf("%d\n", -1);
        return 0;
    }
    for (int i = 1; i <= a; i++)
    {
        for (int j = 1; j <= b; j++)
        {
            printf("%d%c",
                   b % 2 == 1 ? (b * (i - 1) + j <= n ? b * (i - 1) + j : 0)
                              : (i % 2 == 1 ? (b * (i - 1) + j <= n ? b * (i - 1) + j : 0)
                                            : (b * (i - 1) + (b - j + 1) <= n ? b * (i - 1) + (b - j + 1) : 0)),
                   j == b ? '\n' : ' ');
        }
    }
    return 0;
}
```

---

## 作者：_ChongYun_ (赞：0)

两个党派的人分别是奇数和偶数。

可以枚举每一个位置，将奇数与偶数交叉放入，即可保证同党不相邻。

若人数 $n$ 大于椅子数 $ab$，那么一定无解。



---

## 作者：yangzd (赞：0)

# 题目大意：

一个 $a \times b$ 的会场，有 $n$ 个人来开会，问如何安排座位能够使得任意两个奇偶性相同的客人不相邻。

# 分析：
如果 $n > a \times b$ 显然无解，否则看 $b$ 的奇偶性，如果 $b$ 为奇数或者 $a=1$，则把客人按编号从 $1$ 到 $n$ 一排排轮流放即可，这样首先左右相邻的人奇偶性不同，其次上下相邻的人差 $b$ 个位置，即奇数个位置，奇偶性也不同，否则，把客人按编号从 $1$ 到 $n$ 按 $S$ 型放入，左右相邻的人奇偶性依旧不同，而一个在第 $x$ 列的客人与其下面相邻的客人差 $2 \times (b-x)+1$ 个位置，同样是奇数个位置，奇偶性也不同，故按此构造是合法解。

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

long long n,a,b,m[205][205];

signed main()
{
	ios::sync_with_stdio(0);
	
	cin >> n >> a >> b; 
	
    if(n>a*b)
    	cout << "-1" << endl;
    	
    else
    {
        if(b%2 || a==1)
        {
            long long k=1;
            
            for(long long i=1; i<=a; i++)
                for(long long j=1; j<=b; j++)
                    if(k<=n)
						m[i][j]=k++;
						
                    else
						m[i][j]=0;
        }
        
		else
        {
            long long k=1;
            
            for(long long i=1; i<=a; i++)
            {
                if(i%2)
                {
                    for(long long j=1; j<=b; j++)
                        if(k<=n)
							m[i][j]=k++;
							
                        else
							m[i][j]=0;
                }
                
				else 
                {
                    for(long long j=b; j>=1; j--)
                        if(k<=n)
							m[i][j]=k++;
							
                        else
							m[i][j]=0;
                }
            }   
        }
        
        for(long long i=1; i<=a; i++)
            for(long long j=1; j<=b; j++)
            	cout << m[i][j] << " ";  
    }
        
    return 0;
}
```

---

## 作者：Y_J_Y (赞：0)

本着来打一道没有人打的题目练练手，结果刚开始直接思维走偏了，害了我打了很久，还好同机房的一个大佬帮助下纠正了过来

具体的思路大概是一道模拟加上一点找规律的思想吧
（如果他的人数比座位还多，那么直接输出1

然后就进入下一个循环枚举1~k，下面的代码里直接是暴力枚举的，毕竟是cf的A题，应该不会卡（当然是从矩形第一个开始枚举的））
下面的注释
```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <cmath>
using namespace std;
typedef long long ll;
long long i,j;
long long n,a,b;
int main(){
    scanf("%lld%lld%lld",&n,&a,&b);
    long long arr[a][b];//就怕他的数很大
    if (a*b<n){
        cout<<"-1";//坐不下
    }
    else {
        long long k=1;//开始枚举
        for (i=0;i<a;i++){//从第一个开始
            if (i%2==0){//偶数
                for (j=0;j<b;j++){
                    if (k<=n){//找到了
                        arr[i][j]=k;
                        k++;//下一个
                	}
                    else {
                        arr[i][j]=0;
                    }
                }
            }
            else {//奇数
                for (j=b-1;j>=0;j--){//倒着来，想想为甚么
                    if (k<=n){
                        arr[i][j]=k;
                        k++;
                    }
                    else {
                        arr[i][j]=0;
                    }
                }
            }
        }
        for (i=0;i<a;i++){
            for (j=0;j<b;j++){
                cout<<arr[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    return 0;
}
```
完美结束

---

