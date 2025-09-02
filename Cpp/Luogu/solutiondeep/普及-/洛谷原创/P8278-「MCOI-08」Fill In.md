# 题目信息

# 「MCOI-08」Fill In

## 题目背景

$$\begin{aligned}\text{sdjvlajdiofjoiw{\color{1f1e33}n}eglaj}\\\text{pcji{\color{1f1e33}2}gweiruitowoeuri}\\\text{cnvak{\color{1f1e33}5}jflkjweirqoiru}\\\text{rrrwei{\color{1f1e33}f}dlskfjqfafdfaff}\\\text{nmslfjwiejfijlxkjfq{\color{1f1e33}b}el}\\\text{mmm{\color{1f1e33}b}fsfmkdfmksld}\\\text{erjf{\color{1f1e33}n}kerjkwerjkwjeri}\\\text{sdfafafaf{\color{1f1e33}r}fxvzxvzvzx}\end{aligned}$$

## 题目描述

Dream 有一个长度为 $n$（$1\le n\le 10^5$）的正整数数组 $a_1,a_2,\dots,a_n$，其中对于 $i=1,2,\dots,n$，满足 $1\le a_i\le 1000$。

他计算了前缀和数组 $p_i=a_1+a_2+\dots+a_i$，保证对于 **原前缀和数组** 有任意 $1 \le i <n$ 都有 $p_i<p_{i+1}$。

现在 Tommy 偷走了这个数组以及将 $p$ 的若干个元素替代为 $-1$。给定当前的 $p$ 数组，请恢复任意一组合法 $a_1,a_2,\dots,a_n$，可证明一定存在一个数组 $a_i$ 满足要求。

## 说明/提示

#### 样例 1 解释

输出的序列 $a_i$ 一定满足要求：

- $p_1=10=a_1$；
- $p_3=20=a_1+a_2+a_3$；
- $p_5=30=a_1+a_2+a_3+a_4+a_5$。

#### 数据规模与约定

对于 $100\%$ 的数据，$1\le n,\sum n\le 10^5$，并保证存在至少一个合法 $a$ 数组。

 - Subtask 1（50 pts）：对于 $i=1,2,\dots,n$，$p_i\neq -1$；
 - Subtask 2（30 pts）：保证不存在 $i$ 使得 $p_i=p_{i+1}=-1$；
 - Subtask 3（20 pts）：无特殊限制。

## 样例 #1

### 输入

```
2
5
10 -1 20 -1 30
6
-1 -1 -1 -1 -1 -1```

### 输出

```
10 5 5 5 5
1 1 4 5 1 4```

# AI分析结果

• 综合分析与结论：
    - 思路方面：各题解均围绕根据含 -1 的前缀和数组还原原数组展开。50分做法基本是利用前缀和公式直接差分，100分做法的核心思路是将两个非 -1 前缀和之间的差值平摊到对应区间，以满足 \(1 \leq a_i \leq 1000\) 的条件，同时处理好末尾为 -1 的情况。
    - 算法要点：主要涉及前缀和、差分概念，以及对区间和的平均分配处理。
    - 解决难点：避免构造出的 \(a_i\) 大于1000 ，部分题解通过平摊差值，部分通过对超出1000的值进行向前传递调整来解决。
    - 质量评估：多数题解思路清晰，代码有注释辅助理解，但在代码可读性、优化程度上有差异。

所选的题解：
  - **作者：Dream_weavers (5星)**
    - **关键亮点**：思路清晰，分50分和100分做法详细阐述，100分做法中通过结构体数组记录非 -1 端点和区间和，方便区间修改，对区间和的分配讲解细致，并给出具体例子辅助理解，代码可读性高。
    - **个人心得**：因被特定数据hack，修改了部分内容，强调了防止 \(a_i>1000\) 的处理细节。
    - **核心代码片段**：
```cpp
struct node{//结构体
    int l,r,sum;    
}f[N];
void mem(){//初始化
    for(int i=1;i<=n;i++){
        f[i].l=f[i].r=f[i].sum=0;
        a[i]=p[i]=0;
    }
}
signed main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        cnt=1;
        f[cnt].l=1;//提前将l设为1
        for(int i=1;i<=n;i++){
            scanf("%d",&p[i]);//输入p数组
            if(p[i]!=-1){//如果不等于-1
                f[cnt].r=i;//记录r
                f[cnt].sum=p[f[cnt].r]-p[f[cnt].l-1];
                cnt++;//记录sum，更新下标
                f[cnt].l=i+1;//记录下一组的l
            }
        }
        for(int i=1;i<cnt;i++){//循环结构体数组f
            int l=f[i].l,r=f[i].r,sum=f[i].sum;
            int shang,yu;
            shang=sum/(r-l+1);//计算shang
            for(int j=l;j<=r;j++)a[j]=shang;//修改
            if(sum%(r-l+1)>0){//如果yu大于0
                //之前这里被hack了
                yu=sum-shang*(r-l+1);//计算yu
                for(int j=l;j<l+yu;j++)a[j]++;//从l到l+yu-1让每个数加1
            }
        }   
        for(int i=1;i<=n;i++){
            if(a[i]==0)a[i]=1;//如果没修改就变成1
            printf("%d ",a[i]); 
        }
        printf("\n");   
        mem();
    }
    return 0;
}
```
核心实现思想：先通过结构体数组记录前缀和数组中不为 -1 的两个端点和区间和，然后遍历结构体数组，将区间和平均分到对应区间，并处理余数，最后将未修改的 \(a_i\) 设为1。

  - **作者：TheSky233 (4星)**
    - **关键亮点**：按子任务逐步分析，思路连贯，对Subtask 3中避免 \(a_i \geq 1000\) 的情况，通过平摊差值并上取整的方式解决，代码简洁，有对关键步骤的注释说明。
    - **个人心得**：因被hack数据修改了代码中对平摊值计算的问题，强调上取整的原因是减轻后续 \(a_i\) 的负担，避免超出1000。
    - **核心代码片段**：
```cpp
signed main(){
	read(T);
	while(T--){
		read(n);
		for(int i=1;i<=n;i++) read(pre[i]);
		fill(a+1,a+n+1,0);
		fill(b+1,b+n+1,0);
		for(int i=1;i<=n;i++){
			if(pre[i]==-1 &&!a[i]){//是-1且没被填过
				int j=i;
				for(;pre[j]==-1 && j<=n;j++);//找连续的一段-1
				if(j>n){//p[i]到p[n]全是-1
					for(int k=i;k<j;k++){
						a[k]=1;
						b[k]=b[k-1]+1;
					}
				}
				else for(int k=i;k<j;k++){//按上文说的填
					a[k]=ceil((pre[j]-pre[i-1])*1.0/(j-i+1));//upd
					b[k]=b[k-1]+a[k];
				}
			}
			else if(!a[i]){//普通情况
				a[i]=pre[i]-b[i-1];
				b[i]=pre[i];
			}
		}
		for(int i=1;i<=n;i++) write(a[i]),putchar(' '); puts("");
	}
	return 0;
}
```
核心实现思想：遍历前缀和数组，对于 -1 且未填过的位置，找到连续 -1 区间，若到末尾则全填1，否则平摊后续非 -1 前缀和与当前前缀和的差值并上取整；对于普通情况，直接按前缀和公式计算 \(a_i\)。

  - **作者：alex_liu (4星)**
    - **关键亮点**：先介绍c++整除性质作为前置知识，思路上对不同情况分类讨论清晰，通过自定义函数查找最近前缀和位置，代码简洁明了，还设置思考题加深对平均分配的理解。
    - **核心代码片段**：
```cpp
inline int findid(int s){
	for(int i=s;i<=n;i++){
		if(p[i]!=-1)return i;
	}
	return -1;
}
signed main(){
	t=read();
	p[0]=0;
	while(t--){
		n=read();
		for(int i=1;i<=n;i++)p[i]=read();
		int q=findid(1),lq=0;
		if(q==-1){
			for(int i=1;i<=n;i++)cout<<i<<" ";
			cout<<endl;
		}else{
			while(1){
				if(lq==n)break;
				if(lq<n&&q==-1){
					for(int i=lq+1;i<=n;i++)cout<<1<<" ";
					break;
				}
				gc=p[q]-p[lq]; 
				if(gc==1){
					for(int i=lq+1;i<q;i++)cout<<0<<" ";
					cout<<1<<" ";
				}else if(gc==0){
					for(int i=lq+1;i<=q;i++)cout<<0<<" ";
				}else{
					int qq=gc/(q-lq);
					if(qq*(q-lq)!=gc){
						for(int i=lq+1;i<q;i++)cout<<qq<<" ";
						cout<<gc-(q-lq-1)*qq<<" ";
					}else{
						for(int i=lq+1;i<=q;i++)cout<<qq<<" ";
					}
				}
				lq=q;
				q=findid(q+1);
			}
			cout<<endl;
		}
	}
	return 0;
}
```
核心实现思想：通过 `findid` 函数查找最近非 -1 前缀和位置，根据上一个和当前非 -1 前缀和的位置及差值，分5种情况讨论，包括结束、末尾全 -1 、差值为1、差值为0和正常情况，正常情况按整除与否平均分配差值。

最优关键思路或技巧：将两个非 -1 前缀和之间的差值平摊到对应区间的做法最优，能有效避免 \(a_i\) 超出范围，同时结合对特殊情况（如末尾为 -1 ）的处理，可准确构造出合法数组。

可拓展之处：同类型题可拓展到其他需要根据部分信息还原原数组且有数值限制的题目，类似算法套路是分析限制条件，合理分配区间和，保证结果合法。

推荐题目：
  - [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：考察对连续子段和的处理，与本题对区间和的处理有相似之处。
  - [P1419 寻找段落](https://www.luogu.com.cn/problem/P1419)：涉及对数组区间的划分与计算，和本题处理前缀和数组区间问题思路相关。
  - [P2032 扫描](https://www.luogu.com.cn/problem/P2032)：同样是对数组进行操作，根据条件处理区间元素，锻炼对数组操作和条件判断的能力。

个人心得摘录与总结：
  - Dream_weavers和TheSky233都因被特定数据hack而修改代码，强调了在处理 \(a_i\) 范围限制时细节的重要性，特别是在平摊差值时，要充分考虑各种边界情况，避免出现超出限制的数值。 

---
处理用时：47.49秒