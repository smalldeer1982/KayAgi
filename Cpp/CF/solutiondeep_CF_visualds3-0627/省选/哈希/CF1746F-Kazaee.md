# 题目信息

# Kazaee

## 题目描述

给出一个长度为 $n$ 的数组 $a$ 和以下两种操作：

- $1\ i\ x$：将 $a_i$ 修改为 $x$。
- $2\ l\ r\ k$：询问在数组区间 $[l, r]$ 内是否每个出现过的正整数的出现次数都是 $k$ 的倍数。（建议参照样例理解）若是则输出 `YES`，若否则输出 `NO`。

## 样例 #1

### 输入

```
10 8
1234 2 3 3 2 1 1 2 3 4
2 1 6 2
1 1 1
2 1 6 2
2 1 9 2
1 10 5
2 1 9 3
1 3 5
2 3 10 2```

### 输出

```
NO
YES
NO
YES
YES```

# AI分析结果



# 随机化哈希结合树状数组

## 算法分类
随机化算法

## 题目分析
### 核心思路
所有题解均采用**随机映射+树状数组**的核心思路：
1. 将每个数值随机映射为哈希值
2. 维护区间哈希和的前缀和
3. 通过多次不同随机映射降低误判率

### 解决难点
1. **必要条件转化**：将出现次数为k倍数转化为区间和为k倍数
2. **错误率控制**：通过30-40次独立随机实验，将错误率降至 $1/2^{30}$ 以下
3. **离散化处理**：统一离散化所有可能出现的数值以压缩值域

## 题解评分 (≥4星)
1. **fanypcd**（★★★★★）  
   - 思路清晰，正确性分析严谨  
   - 完整离散化处理，高效树状数组实现  
   - 使用mt19937生成高质量随机数

2. **Terac**（★★★★☆）  
   - 理论分析深入，错误率计算详细  
   - 时间复杂度分析明确  
   - 代码结构清晰，可读性强

3. **DengDuck**（★★★★☆）  
   - 多哈希策略提高正确率  
   - 动态参数调整实现灵活  
   - 代码风格简洁高效

## 最优技巧提炼
1. **随机映射策略**  
   ```cpp
   mt19937 rnd(time(0));
   for(int T=1; T<=30; T++){
       for(int i=1; i<=tot; i++) 
           Ref[i] = rnd() >> 1;
       // 维护树状数组...
   }
   ```
   每个数值独立生成随机权值，保证不同实验间独立性

2. **离散化优化**  
   ```cpp
   sort(num+1, num+ntot+1);
   ntot = unique(num+1, num+ntot+1) - num -1;
   a[i] = lower_bound(num+1, num+ntot+1, a[i]) - num;
   ```
   统一离散化原始数据和修改值，减少内存占用

3. **复合验证机制**  
   ```cpp
   if(ans[i] &= (qry(l,r) % k == 0))
   ```
   通过位与操作累积多次实验结果，任一失败即判定失败

## 可视化算法演示
### 动画设计
1. **数值映射阶段**  
   - 展示原始数组值→随机哈希值映射过程  
   - 不同颜色区分不同实验的哈希值

2. **树状数组更新**  
   - 高亮修改操作的传播路径：  
     ![树状数组更新动图](https://oi-wiki.org/ds/images/fenwick-update.gif)

3. **区间查询验证**  
   - 动态显示前缀和差值计算  
   - 失败时显示红色警示，成功显示绿色标记

### 复古像素风格
```javascript
// 像素化数值显示
ctx.fillStyle = '#8B8B83';
ctx.fillRect(x*16, y*16, 15, 15);
ctx.fillStyle = '#FFD700';
ctx.fillText(val, x*16+2, y*16+12);
```
- 使用16x16像素网格  
- 8-bit音效：成功时播放《超级马里奥》金币音效，失败时播放《塞尔达》警告音

## 同类型题目
1. [CF840D - Destiny](https://codeforces.com/problemset/problem/840/D)  
   出现频率超过阈值的元素查询

2. [P6273 魔法](https://www.luogu.com.cn/problem/P6273)  
   特殊区间性质验证

3. [P3730 曼哈顿交易](https://www.luogu.com.cn/problem/P3730)  
   区间出现频率相关查询

## 核心代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
mt19937_64 rnd(time(0));

int a[N],n,q,ls[N<<1],cnt;
map<int,int> hsh;
int rval[N<<1][30]; // 30组随机权值

struct Fenwick{
    long long tr[N];
    void upd(int p,int v){
        for(;p<=n;p+=p&-p) tr[p]+=v;
    }
    long long qry(int p){
        long long res=0;
        for(;p;p-=p&-p) res+=tr[p];
        return res;
    }
}T[30];

int main(){
    scanf("%d%d",&n,&q);
    // 离散化处理
    for(int i=1;i<=n;i++) 
        scanf("%d",a+i), ls[++cnt]=a[i];
    for(int i=1;i<=q;i++){
        int op,l,r,k;
        scanf("%d%d%d",&op,&l,&r);
        if(op==1) ls[++cnt]=r;
        else scanf("%d",&k);
    }
    sort(ls+1,ls+cnt+1);
    cnt=unique(ls+1,ls+cnt+1)-ls-1;
    
    // 初始化随机权值
    for(int i=1;i<=cnt;i++)
        for(int j=0;j<30;j++)
            rval[i][j]=rnd();
    
    // 构建树状数组
    for(int j=0;j<30;j++){
        for(int i=1;i<=n;i++){
            int v=lower_bound(ls+1,ls+cnt+1,a[i])-ls;
            T[j].upd(i,rval[v][j]);
        }
    }
    
    // 处理查询
    while(q--){
        int op,l,r,k;
        scanf("%d",&op);
        if(op==1){
            // 修改操作
            int pos=new_val;
            for(int j=0;j<30;j++){
                int old=rval[old_id][j];
                int nw=rval[new_id][j];
                T[j].upd(pos,nw-old);
            }
        }else{
            // 查询操作
            bool ok=true;
            for(int j=0;j<30;j++){
                long long sum=T[j].qry(r)-T[j].qry(l-1);
                if(sum%k!=0) ok=false;
            }
            puts(ok?"YES":"NO");
        }
    }
}
```

## 关键参数说明
1. **随机实验次数**：30次平衡时间与正确性
2. **离散化处理**：将1e9的值域压缩至6e5级别
3. **树状数组**：O(logn)时间完成单点更新和区间查询

## 学习建议
1. 掌握**离散化**的标准写法
2. 理解**蒙特卡洛方法**在算法中的应用
3. 熟练树状数组的**动态维护**技巧
4. 通过可视化工具观察不同k值下的错误率变化

---
处理用时：68.97秒