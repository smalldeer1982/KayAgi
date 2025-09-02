# 题目信息

# [CERC2013] Crane

## 题目描述

有 $n$ 个箱子等着装上船。箱子的编号是 $a_1,a_2,\cdots,a_n$。你的工作是通过若干次交换，将它们从小到大排列。你每次可以选择一个区间，将它的前半部分与后半部分交换，两半内部的顺序保持不变。你最多可以交换 $531441$ 次。

## 样例 #1

### 输入

```
2
6
5 4 6 3 2 1
5
1 2 3 4 5
```

### 输出

```
5
1 2
4 5
5 6
4 5
1 6
0
```

# AI分析结果

### 算法分类
构造

### 综合分析与结论
本题的核心是通过交换区间的前半部分和后半部分来将序列排序。两位作者都采用了贪心的策略，逐步将每个元素归位，确保后续操作不会影响已经归位的元素。Lemansky的题解通过每次选择区间 $[i, pos_i]$ 来归位元素，并调整区间长度以确保其为偶数。mahaorui2012的题解则采用了类似二分的方法，逐步缩小元素的位置范围，最终将其归位。两种方法的时间复杂度均为 $O(n^2)$，但实际运行效率较高，能够通过题目限制。

### 所选题解
1. **Lemansky (4星)**
   - **关键亮点**：通过贪心策略逐步归位元素，确保每次操作不影响已归位的元素。代码简洁，思路清晰。
   - **个人心得**：通过调整区间长度确保其为偶数，避免了不必要的复杂操作。

   ```cpp
   int t,n,m,a[10005],b[10005];//b数组存位置
   int s,l[114514],r[114514];
   int main(){
       ios::sync_with_stdio(0);
       cin.tie(0);cout.tie(0);
       cin>>t;
       while(t--){
           cin>>n,m=1,s=0;
           for(int i=1;i<=n;++i) cin>>a[i],b[a[i]]=i;
           while(1){
               while(b[m]==m) ++m;
               if(m>n) break;
               while(b[m]!=m){//还没归位
                   ++s,l[s]=m+(b[m]-m+1)%2,r[s]=b[m];
                   int w=(l[s]+r[s])/2;
                   for(int i=l[s];i<=w;++i){
                       swap(a[i],a[i+w-l[s]+1]);
                       swap(b[a[i]],b[a[i+w-l[s]+1]]);
                   }
               }
           }
           cout<<s<<'\n';
           for(int i=1;i<=s;++i) cout<<l[i]<<' '<<r[i]<<'\n';
       }
       return 0;
   }
   ```

2. **mahaorui2012 (4星)**
   - **关键亮点**：采用类似二分的方法逐步缩小元素的位置范围，最终将其归位。思路清晰，代码实现较为高效。
   - **个人心得**：通过哈希表快速定位元素位置，提高了操作效率。

   ```cpp
   int arr[10005];
   int hsh[10005];

   void mswap(int l,int r){
       int len=(r-l+1)/2;
       for(int i=0;i<len;++i){
           swap(arr[l+i],arr[l+i+len]);
           swap(hsh[arr[l+i]],hsh[arr[l+i+len]]);
       }
   }

   struct oper{
       int l,r;
   } oparr[140005];
   int p=0;

   int main(){
       int t;
       cin>>t;
       while(t--){
           p=0;
           int n;
           cin>>n;
           for(int i=1;i<=n;++i){
               cin>>arr[i];
               hsh[arr[i]]=i;
           }
           for(int i=1;i<=n;++i){
               int r=n;
               while(r-i>=1){
                   int mid=(i+r-(r-i)%2)/2;
                   if(hsh[i]>mid){
                       mswap(i+(r-i+1)%2,r);
                       oparr[++p].l=i+(r-i+1)%2;oparr[p].r=r;
                   }r=mid;
               }
           }
           cout<<p<<'\n';
           for(int i=1;i<=p;++i){
               cout<<oparr[i].l<<' '<<oparr[i].r<<'\n';
           }
            
       }return 0;
   }
   ```

### 最优关键思路或技巧
- **贪心策略**：逐步将每个元素归位，确保后续操作不影响已归位的元素。
- **区间调整**：通过调整区间长度确保其为偶数，避免不必要的复杂操作。
- **哈希表**：通过哈希表快速定位元素位置，提高操作效率。

### 可拓展之处
类似的问题可以通过贪心策略和构造方法解决，尤其是在需要逐步归位元素的场景中。例如，某些排序问题或排列问题可以通过类似的思路进行优化。

### 推荐题目
1. [P1177 【模板】快速排序](https://www.luogu.com.cn/problem/P1177)
2. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)
3. [P1068 分数线划定](https://www.luogu.com.cn/problem/P1068)

---
处理用时：24.21秒