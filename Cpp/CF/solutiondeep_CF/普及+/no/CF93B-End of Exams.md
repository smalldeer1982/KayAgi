# 题目信息

# End of Exams

## 题目描述

Students love to celebrate their holidays. Especially if the holiday is the day of the end of exams!

Despite the fact that Igor K., unlike his groupmates, failed to pass a programming test, he decided to invite them to go to a cafe so that each of them could drink a bottle of... fresh cow milk. Having entered the cafe, the $ m $ friends found $ n $ different kinds of milk on the menu, that's why they ordered $ n $ bottles — one bottle of each kind. We know that the volume of milk in each bottle equals $ w $ .

When the bottles were brought in, they decided to pour all the milk evenly among the $ m $ cups, so that each got a cup. As a punishment for not passing the test Igor was appointed the person to pour the milk. He protested that he was afraid to mix something up and suggested to distribute the drink so that the milk from each bottle was in no more than two different cups. His friends agreed but they suddenly faced the following problem — and what is actually the way to do it?

Help them and write the program that will help to distribute the milk among the cups and drink it as quickly as possible!

Note that due to Igor K.'s perfectly accurate eye and unswerving hands, he can pour any fractional amount of milk from any bottle to any cup.

## 样例 #1

### 输入

```
2 500 3
```

### 输出

```
YES
1 333.333333
2 333.333333
2 166.666667 1 166.666667
```

## 样例 #2

### 输入

```
4 100 5
```

### 输出

```
YES
3 20.000000 4 60.000000
1 80.000000
4 40.000000 2 40.000000
3 80.000000
2 60.000000 1 20.000000
```

## 样例 #3

### 输入

```
4 100 7
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
5 500 2
```

### 输出

```
YES
4 250.000000 5 500.000000 2 500.000000
3 500.000000 1 500.000000 4 250.000000
```

# AI分析结果

### 题目翻译
# 考试结束

## 题目描述
学生们喜欢庆祝他们的假期。尤其是如果这个假期是考试结束的日子！
尽管伊戈尔·K和他的同学们不同，他没有通过编程测试，但他还是决定邀请他们去咖啡馆，这样他们每个人都可以喝一瓶……新鲜的牛奶。走进咖啡馆后，这$m$个朋友在菜单上发现了$n$种不同的牛奶，所以他们点了$n$瓶——每种一瓶。我们知道每瓶牛奶的容量都等于$w$。
当牛奶瓶被端上来时，他们决定把所有的牛奶平均分配到$m$个杯子里，这样每个人都能得到一杯。作为对没有通过测试的惩罚，伊戈尔被指定为倒牛奶的人。他抗议说他害怕弄混，建议这样分配饮料：每瓶牛奶最多只倒入两个不同的杯子。他的朋友们同意了，但他们突然面临一个问题——到底该怎么做呢？
帮助他们并编写一个程序，帮助将牛奶分配到杯子中，以便尽快喝到牛奶！
注意，由于伊戈尔·K有极其精准的眼力和稳定的双手，他可以从任何瓶子向任何杯子中倒入任意分数数量的牛奶。

## 样例 #1
### 输入
```
2 500 3
```
### 输出
```
YES
1 333.333333
2 333.333333
2 166.666667 1 166.666667
```

## 样例 #2
### 输入
```
4 100 5
```
### 输出
```
YES
3 20.000000 4 60.000000
1 80.000000
4 40.000000 2 40.000000
3 80.000000
2 60.000000 1 20.000000
```

## 样例 #3
### 输入
```
4 100 7
```
### 输出
```
NO
```

## 样例 #4
### 输入
```
5 500 2
```
### 输出
```
YES
4 250.000000 5 500.000000 2 500.000000
3 500.000000 1 500.000000 4 250.000000
```

### 算法分类
构造

### 综合分析与结论
- **Feyn题解思路**：对人数$m$和饮料数$n$的大小关系分类讨论。当$n\leq m$时，从前向后分配每瓶饮料，当前人填满就换下一个，保证每瓶饮料不超两人分；当$n > m$时，先让$n$个人从每瓶饮料拿该拿部分，剩下$m - n$个人分$n$瓶喝过的饮料，此时需满足$m - n$整除$n$，通过求$m$和$n$的最大公约数判断是否满足条件，最后按不同情况输出分配方案，同时注意精度问题。
- **ran_qwq题解思路**：认为$w$对方案无影响，采用一种尽量使一瓶饮料划分次数不超1的构造方法。将饮料排成一列，对于$i\in[1,m)$，在$\frac{in}{m}$位置分开，第$i$个人获得$[\frac{(i - 1)n}{m},\frac{in}{m}]$部分，若无法划分则无解，同样要注意精度。
- **难点对比**：两者难点都在于如何构造出满足每瓶牛奶最多在两个不同杯子的分配方案。Feyn通过分类讨论，利用数学关系判断可行性并构造；ran_qwq则从直观的划分角度构造，判断依据相对直接。
- **结论**：两篇题解思路清晰，均针对问题给出有效解法，Feyn题解对情况分析更细致，ran_qwq题解构造思路较直观。

### 所选的题解
- **Feyn题解**
  - **星级**：4星
  - **关键亮点**：对人数和饮料数大小关系进行全面分类讨论，利用数论知识（最大公约数）判断可行性，逻辑严谨。
  - **重点代码**：
```cpp
inline int gcd(int s1,int s2){
	return s2==0?s1:gcd(s2,s1%s2);
}
int m,n,num;
signed main(){
	read(m);read(n);read(num);
	double ss=(double)m*n/num;
	if(num>m&&m+gcd(m,num)!=num){
		printf("NO\n");return 0;
	}
	printf("YES\n");
	if(num<=m){
		double want=ss,val=n;int pl=1,wh=1;
		while(wh<=num){
			double now=min(want,val);
			printf("%d %.10f ",pl,now);
			val-=now;want-=now;
			if(want<eps){wh++;want=ss;putchar('\n');}
			if(val<eps)pl++,val=n;
		}
	}
	else{
		for(int i=1;i<=m;i++)printf("%d %.10f\n",i,ss);
		int turn=m/(num-m);
		for(int i=1;i<=num-m;i++){
			for(int j=1;j<=turn;j++)printf("%d %.10f ",(i-1)*turn+j,n-ss);
			putchar('\n');
		}
	}
	return 0;
}
```
核心实现思想：先读入数据，通过判断人数和饮料数关系及最大公约数确定是否有解。有解时，按不同情况分别构造分配方案并输出。
- **ran_qwq题解**
  - **星级**：4星
  - **关键亮点**：构造思路直观，通过对饮料位置划分来确定分配方案，简洁明了。
  - **重点代码**：
```cpp
void QwQ() {
	n=rd(),w=rd(),m=rd();
	for(int i=1;i<=m;i++) a[i]=1.*i*n/m;
	for(int i=1;i<=m;i++) if(ceil(a[i])==ceil(a[i-1])&&floor(a[i])==floor(a[i-1])) return puts("NO"),void();
	puts("YES");
	for(int i=1;i<=m;i++)
		if(ceil(a[i])-floor(a[i-1])==1) printf("%d %.6Lf\n",(int)ceil(a[i]),(a[i]-a[i-1])*w);
		else {
			int st,ed;
			if(floor(a[i-1])!=a[i-1]) printf("%d %.6Lf ",st=(int)ceil(a[i-1]),(ceil(a[i-1])-a[i-1])*w);
			else st=a[i-1];
			if(ceil(a[i])!=a[i]) printf("%d %.6Lf ",ed=(int)ceil(a[i]),(a[i]-floor(a[i]))*w);
			else ed=a[i]+1;
			for(int i=st+1;i<ed;i++) printf("%d %.6Lf ",i,(ldb)w);
			puts("");
		}
}
```
核心实现思想：先读入数据，计算每个划分位置，判断是否可划分，若可划分则按规则输出分配方案。

### 最优关键思路或技巧
- **分类讨论**：对于不同的人数和饮料数关系，分别采用不同的构造方法，使问题解决更有条理。
- **数学判断**：利用数论知识（如最大公约数）判断分配方案的可行性，为构造提供依据。

### 可拓展之处
此类题目属于构造类问题，通常需要根据给定条件设计出满足要求的方案。类似套路是先对问题进行分类，再针对不同类别利用数学知识或直观构造来解决。同类型题常见于资源分配、方案设计等场景，需要在满足特定限制条件下构造出可行方案。

### 推荐洛谷题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举和组合的方式解决数的选取问题，与本题构造分配方案类似，都需满足一定条件。
- [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：利用动态规划思想解决点菜的方案数问题，与本题构造方案的思路有相似之处，都需考虑不同情况。
- [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)：通过搜索算法寻找最优路径，与本题构造满足条件的分配方案类似，都需在多种可能性中找到合适的解。 

---
处理用时：69.96秒