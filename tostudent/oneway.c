/*
 **********************************************
 *  CS314 Principles of Programming Languages *
 *  Fall 2018                                 *
 *  File: oneway.c                            *
 *  Date: 11/25/2018                          *
 **********************************************
 */
#include "oneway.h"
#include "utils.h"

void extend_one_hand(int threadId, int threadNum, GraphData graph,
                     int nodeNum, int *nodeToProcess,
                     int *res, int *strongNeighbor)
{

    int i = threadId;
    int wordChunk = (nodeNum+threadNum-1)/threadNum;
    int beg = i * wordChunk;
    int end = (beg+wordChunk<nodeNum) ? beg+wordChunk : nodeNum; 

    int curr;
    int k;

    int * temp;  
    for(curr = beg; curr <= end-1; curr++){
        temp = graph.index+graph.offset[nodeToProcess[curr]]; // The list of neighbors for curr
        strongNeighbor[nodeToProcess[curr]] = -1;
        for(k = 0; k < graph.degree[nodeToProcess[curr]]; k++){
            if(res[temp[k]] == UNMATCHED){
                strongNeighbor[nodeToProcess[curr]] = temp[k];
                break; 
            }
        }
        //code for node matching 
    }
    
     //Do we have to find the least index in this algorithm?
    /* Vi = the set of vertices assigned to thread i
        N(k) = the set of (sorted) neighbors for vertex k
        for each v in Vi
            for each u in N(v) do
                if (res[u] == UNMATCHED) then
                strongNeighbor[v] = u
            break out loop u
                end if
            end for
            end for */
}

void check_handshaking(int threadId, int threadNum,
                       int nodeNum, int *nodeToProcess,
                       int *strongNeighbor, int *res)
{
    int i = threadId;
    int wordChunk = (nodeNum+threadNum-1)/threadNum;
    int beg = i * wordChunk;
    int end = (beg+wordChunk<nodeNum) ? beg+wordChunk : nodeNum; 
    int curr;
    
    for(curr = beg; curr<=end-1; curr++){
        int s = strongNeighbor[nodeToProcess[curr]];
        if(s == UNMATCHED){
            res[nodeToProcess[curr]] = NO_MATCHED_NODES;
        }
        else if(nodeToProcess[curr] == strongNeighbor[s])
            res[nodeToProcess[curr]] = s;
        }
       
    /* 
        Vi = the set of vertices assigned to thread i
        for each v in Vi do
            s = strongNeighbor[v]
            if (v == strongNeighbor[s]) then
                res[v] = s
            end if
        end for
    */
}


