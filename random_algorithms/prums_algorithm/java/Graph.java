import java.util.*;

public class Graph {
  private final static int infinite = 999999999;
  int [][] LinkCost;
  int NNodes;
  Graph(int[][] mat) {
    int i, j;
    NNodes = mat.length;
    LinkCost = new int[NNodes][NNodes];
    for (i = 0; i < NNodes; i++) {
      for (j = 0; j < NNodes; j++) {
        LinkCost[i][j] = mat[i][j];
        if (LinkCost[i][j] == 0) LinkCost[i][j] = infinite;
      }
    }
    for (i = 0; i < NNodes; i++) {
      for (j = 0; j < NNodes; j++) {
        if (LinkCost[i][j] < infinite) System.out.print(" " + LinkCost[i][j] + " ");
        else System.out.print(" * ");
      }
      System.out.println();
    }
  }
  public int unReached(boolean[] r) {
    boolean done = true;
    for (int i = 0; i < r.length; i++) {
      if (r[i] == false) return i;
    }
    return -1;
  }
  public void Prim() {
    boolean[] Reached = new boolean[NNodes];
    int[] predNode = new int[NNodes];
    Reached[0] = true;
    for (int k = 1; k < NNodes; k++) {
      Reached[k] = false;
    }
    predNode[0] = 0;
    printReachSet(Reached);
    System.out.println();
    int x, y;
    for (int k = 1; k < NNodes; k++) {
      x = y = 0;
      for (int i = 0; i < NNodes; i++) {
        for (int j = 0; j < NNodes; j++) {
          if (Reached[i] && !Reached[j] && LinkCost[i][j] < LinkCost[x][y]) {
            x = i; 
            y = j;
          }
        }
      }
      System.out.println("Min cost edge: (" + x + ", " + y + ") cost = " + LinkCost[x][y]);
      predNode[y] = x;
      Reached[y] = true;
      printReachSet(Reached);
      System.out.println();
    }
    int[] a = predNode;
    for (int i = 0; i < NNodes; i++) {
      System.out.println(a[i] + " --> " + i);
    }
  }
  void printReachSet(boolean[] Reached) {
    System.out.print("ReachSet = ");
    for (int i = 0; i < Reached.length; i++) if (Reached[i]) System.out.print(i + " ");
  }
}
