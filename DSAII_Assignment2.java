// DSA-II Assignment 2: Sliding Window Technique
import java.util.*;

public class DSAII_Assignment2 {
    static long maxSumBrute(int[] a, int k) {
        if (k < 1 || k > a.length) throw new IllegalArgumentException("Part A requires 1 <= K <= n.");
        long best = Long.MIN_VALUE;
        for (int i=0; i+k<=a.length; i++) {
            long sum=0;
            for (int j=i; j<i+k; j++) sum += a[j];
            best=Math.max(best,sum);
        }
        return best;
    }
    static long maxSumSliding(int[] a, int k) {
        if (k < 1 || k > a.length) throw new IllegalArgumentException("Part A requires 1 <= K <= n.");
        long sum=0;
        for(int i=0;i<k;i++) sum+=a[i];
        long best=sum;
        for(int right=k;right<a.length;right++){
            sum += (long)a[right]-a[right-k];
            best=Math.max(best,sum);
        }
        return best;
    }
    static class Result {
        int length,start,end;
        Result(int l,int s,int e){length=l;start=s;end=e;}
        public String toString(){return "("+length+","+start+","+end+")";}
    }
    static void validateB(int[] a,int k) {
        if(k<0) throw new IllegalArgumentException("Part B limit K must be non-negative.");
        for(int x:a) if(x<0) throw new IllegalArgumentException("Part B requires non-negative array values.");
    }
    static Result longestBrute(int[] a,int k) {
        validateB(a,k); Result best=new Result(0,-1,-1);
        for(int left=0;left<a.length;left++){
            long sum=0;
            for(int right=left;right<a.length;right++){
                sum+=a[right];
                if(sum<=k && right-left+1>best.length) best=new Result(right-left+1,left,right);
            }
        }
        return best;
    }
    static Result longestSliding(int[] a,int k) {
        validateB(a,k); int left=0; long sum=0; Result best=new Result(0,-1,-1);
        for(int right=0;right<a.length;right++){
            sum+=a[right];
            while(sum>k && left<=right) sum-=a[left++];
            int len=right-left+1;
            if(len>best.length) best=new Result(len,left,right);
        }
        return best;
    }
    static String arr(int[] a){return Arrays.toString(a);}
    static void showA(int[] a,int k){System.out.println("Array: "+arr(a)+", K="+k+" | brute="+maxSumBrute(a,k)+" | sliding="+maxSumSliding(a,k));}
    static void showB(int[] a,int k){System.out.println("Array: "+arr(a)+", limit="+k+" | brute="+longestBrute(a,k)+" | sliding="+longestSliding(a,k));}
    public static void main(String[] args){
        System.out.println("DSA-II Assignment 2: Sliding Window Technique\n\nPART A: Maximum sum of K consecutive elements");
        showA(new int[]{2,1,5,1,3,2},3); showA(new int[]{-4,-2,-7},2);
        showA(new int[]{6},1); showA(new int[]{1,2,3},3);
        System.out.println("\nPART B: Longest subarray with sum at most K (0-based indices)");
        showB(new int[]{1,2,1,1,3},4); showB(new int[]{5,1,1},2);
        showB(new int[]{4,2,1},0); showB(new int[]{0,0,1,0},1);
    }
}
