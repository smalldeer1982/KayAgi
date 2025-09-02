# Something with XOR Queries

## 题目描述

This is an interactive problem.

Jury has hidden a permutation $ p $ of integers from $ 0 $ to $ n-1 $ . You know only the length $ n $ . Remind that in permutation all integers are distinct.

Let $ b $ be the inverse permutation for $ p $ , i.e. $ p_{bi}=i $ for all $ i $ . The only thing you can do is to ask xor of elements $ p_{i} $ and $ b_{j} $ , printing two indices $ i $ and $ j $ (not necessarily distinct). As a result of the query with indices $ i $ and $ j $ you'll get the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870D/05028eedea6284512040197fbf5778282a77d5c1.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870D/4298d47c0191af3c0a3103f431751061bc7e2362.png) denotes the xor operation. You can find the description of xor operation in notes.

Note that some permutations can remain indistinguishable from the hidden one, even if you make all possible $ n^{2} $ queries. You have to compute the number of permutations indistinguishable from the hidden one, and print one of such permutations, making no more than $ 2n $ queries.

The hidden permutation does not depend on your queries.

## 说明/提示

xor operation, or bitwise exclusive OR, is an operation performed over two integers, in which the $ i $ -th digit in binary representation of the result is equal to $ 1 $ if and only if exactly one of the two integers has the $ i $ -th digit in binary representation equal to $ 1 $ . For more information, see [here](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

In the first example $ p=[0,1,2] $ , thus $ b=[0,1,2] $ , the values ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870D/05028eedea6284512040197fbf5778282a77d5c1.png) are correct for the given $ i,j $ . There are no other permutations that give the same answers for the given queries.

The answers for the queries are:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870D/46dc5fa94694b483f32f322d24785fe68067b25b.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870D/a7c48fc1d69c2a31eb1045df7d8372d886447c99.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870D/110cedaea37a8029cc469f48f789efcb5cd1135a.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870D/0ddcfac860c29dd6a8df9924ebc0e40d8aa6ba25.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870D/91072cc5c414f3abeea20c2283336f4fdb1f8e87.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870D/b587b2585b6e8e5b2a4afb82178cfced90807af0.png).

In the second example $ p=[3,1,2,0] $ , and $ b=[3,1,2,0] $ , the values ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870D/05028eedea6284512040197fbf5778282a77d5c1.png) match for all pairs $ i,j $ . But there is one more suitable permutation $ p=[0,2,1,3] $ , $ b=[0,2,1,3] $ that matches all $ n^{2} $ possible queries as well. All other permutations do not match even the shown queries.

## 样例 #1

### 输入

```
3
0
0
3
2
3
2```

### 输出

```
? 0 0
? 1 1
? 1 2
? 0 2
? 2 1
? 2 0
!
1
0 1 2```

## 样例 #2

### 输入

```
4
2
3
2
0
2
3
2
0```

### 输出

```
? 0 1
? 1 2
? 2 3
? 3 3
? 3 2
? 2 1
? 1 0
? 0 0
!
2
3 1 2 0```

# 题解

## 作者：GalaxyOier (赞：2)

## **题意：**
给你一个排列 $p$ 和对应的位置 $b$，也就是说 $p[b[i]]=i$，然后给你最多询问 $2n$ 次找出所有的 $p$ 排列，然后任意输出一个。
    
## **题解：**
其实是一道水题。

要知道一共 $n$ 个数询问 $2n$ 次,
也就是说能够询问 $p[0]^{b[i]}(0<=i<n)$ 和 $p[i]^{b[0]}(0<=i<n)$，然后只要给$p[0]$ 赋一个值所有的值就都出来了，然后就简单了。
    
## **代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans[5500][5500],p[5500],b[5500],p_true[5500],b_true[5500];
int main() 
{
    int n;
    scanf("%d",&n);
    int x;
    for(int i=0;i<n;i++) 
    {
        printf("? %d %d\n",i,0);
        fflush(stdout);
        scanf("%d",&x);
        ans[i][0]=x;
    }
    for(int i=1;i<n;i++) 
    {
        printf("? %d %d\n" , 0 , i);
        fflush(stdout);
        scanf("%d" , &x);;
        ans[0][i] = x;
    }
    int res = 0;
    for(int i = 0 ; i < n ; i++) 
    {
        memset(p , -1 , sizeof(p));
        memset(b , -1 , sizeof(b));
        p[0] = i;
        for(int j = 0 ; j < n ; j++) 
        {
            b[j] = (ans[0][j] ^ p[0]);
        }
        for(int j = 1 ; j < n ; j++) 
        {
            p[j] = (ans[j][0] ^ b[0]);
        }
        int flag = 0;
        for(int j = 0 ; j < n ; j++) 
        {
            if(p[b[j]] != j || p[j] >= n || b[j] >= n)
            {
                flag = 1;
                break;
            }
        }
        if(!flag) 
        {
            res++;
            for(int j = 0 ; j < n ; j++) 
            {
                p_true[j] = p[j];
                b_true[j] = b[j];
            }
        }
    }
    printf("!\n");
    printf("%d\n" , res);
    for(int i=0;i<n;i++)
    {
        printf("%d ",p_true[i]);
    }
    printf("\n");
    fflush(stdout);
    return 0;
}
```



---

## 作者：William_Wang_ (赞：1)

- 我们先来看在已知 $n^2$ 对数的情况下下

	此时仍然存在多组解, 我们可以通过枚举 $p_0$ 的值, 根据 $n^2$ 对数来确定所有 $p_i$ 以及 $b_i$ 的值,  再检查是否满足 $p[b[i]]=i$



- 而当我们已知 
 
 	- $p_0 \land b_0,\space p_1 \land b_0,\space p_2 \land b_0,\space p_3 \land b_0\space ....\space  p_{n-1} \land b_0\space$ 

	- $p_0 \land b_0,\space p_0 \land b_1,\space p_0 \land b_2,\space p_0 \land b_3\space ....\space  p_0 \land b_{n-1}\space$ 

	对于任意 $p_i \land b_j$ , 可以用 $(p_i \land b_0) \land (p_0 \land b_0)\land (p_0 \land b_j)$ 来表示

- 我们只需知道这 $2n$ 对数即可推出所有的 $n^2$ 对数

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int n, p0[5005], b0[5005], p[5005], b[5005], vis[5005];
bool valid(int *a)
{
    memset(vis,0,sizeof(vis));
    for(int i=0;i<n;i++)
    {
        if(a[i] >= n) return false;
        vis[a[i]]++;
    }
    for(int i=0;i<n;i++)
        if(vis[i]!=1) return false;
    return true;
}
bool check(int x)
{
    p[0] = x;
    for(int i=1;i<n;i++)
        p[i] = p[0] ^ b0[0] ^ b0[i];    // p0 ^ (p0 ^ b0) ^ (pi ^ b0)
    
    if(!valid(p)) return false;
    
    b[0] = p[0] ^ p0[0];
    for(int i=1;i<n;i++)
        b[i] = b[0] ^ p0[0] ^ p0[i];    // b0 ^ (p0 ^ b0) ^ (p0 ^ bi)
    
    if(!valid(b)) return false;
    
    for(int i=0;i<n;i++)
        if(p[b[i]] != i) return false;
    
    return true;
}
int main()
{
    cin >> n;
    for(int i=0;i<n;i++)
    {
        printf("? 0 %d\n",i); fflush(stdout);
        scanf("%d",&p0[i]);
    }
    for(int i=0;i<n;i++)
    {
        printf("? %d 0\n",i); fflush(stdout);
        scanf("%d",&b0[i]);
    }
    int cnt = 0;
    for(int i=0;i<n;i++)
    {
        if(check(i)) cnt++;
    }
    printf("!\n%d\n",cnt);
    for(int i=0;i<n;i++)
    {
        if(check(i))
        {
            p[0] = i;
            printf("%d ",p[0]);
            for(int j=1;j<n;j++) printf("%d ",p[0] ^ b0[0] ^ b0[j]);
            break;
        }
    }
    puts("");
    fflush(stdout);
}

```

---

## 作者：lgx57 (赞：0)

其实是一道非常简单的交互题。

题目描述已经提示你了，询问 $n^2$ 词也不能保证只有一个答案。

所以我们可以考虑在 $2n$ 次操作中得到 $n^2$ 次询问得到的答案。

为了方便书写，我这里用 $a$ 代替 $p$。

设 $ans1_i=a_0 \oplus b_j$，$ans2_i=a_i \oplus b_0$。容易发现：

$$a_i \oplus b_j=(a_i \oplus b_0) \oplus (a_0 \oplus b_0) \oplus (a_0 \oplus b_j)$$

于是，我们可以求出每一组 $a_i \oplus b_j$ 的值。

然后就简单了。我们可以枚举 $a_0$，然后可以推出其他数的值，再判断一下是否满足题目要求即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int Ask(int x,int y){//询问
	cout<<"? "<<x<<' '<<y<<endl;
	int ans;
	cin>>ans;
	return ans;
}
const int N=5005;
int ans1[N],ans2[N];
int get(int i,int j){
	return ans1[j]^ans1[0]^ans2[i];//a_i^b_j
}
bool check(vector<int> v1,vector<int> v2){//判断是否满足要求
	for (int i=0;i<n;i++){
		if (v2[i]>=n) return 0;
		if (v1[v2[i]]!=i) return 0;
	}
	return 1;
}
void sol(){
	cin>>n;
	for (int i=0;i<n;i++){
		ans1[i]=Ask(0,i);
		ans2[i]=Ask(i,0);
	}
	int Ans=0;
	vector<int> v1(n),v2(n),v(n);
	for (int i=0;i<n;i++){
		v1[0]=i;
		for (int j=0;j<n;j++){
			v2[j]=v1[0]^get(0,j);
		}
		for (int j=1;j<n;j++){
			v1[j]=v2[0]^get(j,0);
		}//处理出其他的数
		if (check(v1,v2)){
			if (!Ans) v=v1;
			Ans++;
		}
	}
	cout<<"!"<<endl;
	cout<<Ans<<endl;
	for (int x:v) cout<<x<<' ';
	cout<<endl;
}
signed main(){
	sol();
	return 0;
}
```

---

