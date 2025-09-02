# Jury Marks

## 题目描述

有 $k$ 个评委给一个 **初始分数未知的** 参赛者 **依次** 打分，其中第 $i$ 个评委会在第 $i$ 分钟内为参赛者打分，在第 $i$ 分钟结束时参赛者会 **立即** 获得 $a_i$ 的分数。  
给出参赛者在某 $n$ 个 **正整分钟结束时** 的分数 $b_i$，问：这位参赛者可能有多少个 **数值不同的** 初始分数？

## 说明/提示

$1 \leq n \leq k \leq 2 \times 10^3$，$- 2 \times 10^3 \leq a_i \leq 2 \times 10^3$，$- 4 \times 10^6 \leq b_i \leq 4 \times 10^6$，保证 $b_i$ 互不相同，但不保证 $b_i$ 按时间顺序给出。

## 样例 #1

### 输入

```
4 1
-5 5 0 20
10
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 2
-2000 -2000
3998000 4000000
```

### 输出

```
1
```

# 题解

## 作者：qwq___qaq (赞：1)

首先，对 $a$ 做前缀和，得到 $i$ 时刻的加分。

然后枚举 $b_1$ 的对应点 $i$，然后定义 $j$ 依次从 $2$ 到 $n$ 判断 $b_j$ 是否可以得到这个得分。

假设 $b_j$ 对应的是 $k$，有：$a_k-b_j=a_i-b_1$，移项得 $a_k=b_j+a_i-b_1$，右边是定值，也就是说，我们只需要查找 $a$ 中有没有 $b_j+a_i-b_1$。

可以用 `map` 维护，时间复杂度 $O(nk\log k)$。

---

## 作者：Poncirus (赞：1)

因为 $b$ 计算某时刻的总分，$a$ 只表示变化量，所以先将 $a$ 进行前缀和，得到 $i$ 时刻的总加分。

因为 $b$ 是无序的，我们需要确定 $b$ 的顺序。

假设 $c_i$ 为某一时刻的得分，$v$ 为初始分数，易得 $c_i=v+a_i$，进一步得到 $c_i-c_j=v+a_i-(v+a_j)$，化简得 $c_i-c_j=a_i-a_j$。

枚举 $i=1\sim k$，假设 $b_1$ 对应 $c_i$，遍历 $b$，检验是否每个 $b_j$ 都能有对应的 $c_j$，存在条件即为 $b_1-b_j = a_i-a_k$。因为 $b_1$、$b_j$ 和 $a_i$ 已知，查找 $a$ 中是否存在值为 $a_i+b_j-b_1$ 的元素即可。如果任意一个 $b_j$ 找不到对应值，该方案非法。

注意去重即可。

```cpp
namespace XSC062 {
using namespace fastIO;
const int maxn = 2e3 + 5;
int n, k, res;
int a[maxn], b[maxn];
std::set<int> st, st1;
int main() {
	read(n);
	read(k);
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
		a[i] += a[i - 1];
		st.insert(a[i]);
	}
	for (int i = 1; i <= k; ++i)
		read(b[i]);
	for (int i = 1; i <= n; ++i) {
		if (st1.find(a[i]) != st1.end())
			continue;
		st1.insert(a[i]);
		for (int j = 1; j <= k; ++j) {
			if (st.find(a[i] + b[j] - b[1]) == st.end())
				goto NOOOOO;
		}
		++res;
		NOOOOO: ; 
	}
	printf("%d", res);
	return 0;
}
} // namespace XSC062

```

---

## 作者：dztlb (赞：1)

题意简述：给定一个长度为 $k$ 的序列 $a$ 和长度为 $n$ 的序列 $b$ ，问有多少个起始值满足顺次加上序列 $a$ 的过程中能得到 $b$ 中所有数。

对于一个初始值 $num$ ，能够满足 

 $$  num+\sum_{i=1}^{r}a[i]=b[j] (j=1,2,...,n)$$ 
 
 $r$ 为人为指定的不大于 $k$ 的编号。

注意到 $k \leq 2000$ ，所以 $ k^{2} $ 可过。直接考虑根据 $b[1]$ 枚举 $r$ ,从而枚举出所有可能的 $num$ 。再将这 $k$ 个 $num$ 带回序列 $a$ 进行验证，只要该 $num$ 累加的过程中得到所有 $b$ 中元素，则为可行的起始值。

注意对开始生成的 $num$ 进行去重，避免重复计算。

关键代码：

```cpp
const int maxn=100005;
int n,k,a[maxn],pre[maxn],b[maxn];
int que[maxn],ans=0;
bool ok[80000005],flag[80000005];
int main(){
    k=read(),n=read();
    for(register int i=1;i<=k;++i) a[i]=read(),pre[i]=pre[i-1]+a[i];
    for(register int i=1;i<=n;++i){
	//使用桶判断目标b序列的出现情况，由于b存在负数，加上一个大常数。 
        b[i]=read()+4000000;
        ok[b[i]]=1;//标记该数 
    }
    for(register int i=1;i<=k;++i){
        que[i]=b[1]-pre[i];//根据b[1]产生que，即num组成的数组 
    }
    sort(que+1,que+1+k);
    int len=unique(que+1,que+1+k)-que-1;//去重
	//当然也可以在生成que时直接判断去重。 
    for(register int i=1;i<=len;++i){
        int cnt=0,now=que[i];
        memset(flag,0,sizeof(flag));//flag避免同一个b值出现多次时被多次统计 
        for(register int j=1;j<=k;++j){
            now+=a[j];
            if(ok[now]&&!flag[now]) ++cnt,flag[now]=1;
        }
        if(cnt==n) ++ans;//最后只需判断是否n个值都出现 
    }
    cout<<ans<<endl;
    return 0;
}
```


---

