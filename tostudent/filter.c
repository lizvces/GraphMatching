/*
 **********************************************
 *  CS314 Principles of Programming Languages *
 *  Fall 2018                                 *
 *  File: filter.c                            *
 *  Date: 11/25/2018                          *
 **********************************************
 */

#include "filter.h"

void count_unmatched_vertices(int threadId, int threadNum, int nodeNum,
                              int *nodeToProcess, int *res,
                              int *nodeCount)
{

    //This is the part of the program that is giving me the most issues.

    int i = threadId;
    int wordChunk = (nodeNum+threadNum-1)/threadNum;
    int beg = i * wordChunk;
    int end = (beg+wordChunk<nodeNum) ? beg+wordChunk : nodeNum; 
    int curr;
        
    nodeCount[i] = 0;
    
    for(curr = beg; curr<=end-1; curr++){
        if(res[nodeToProcess[curr]] == UNMATCHED){
            nodeCount[i]++;
        }
    }

}

void update_remain_nodes_index(int threadId, int threadNum,
                               int *nodeToProcess, int *startLocations,
                               int *res,
                               int nodeNum, int *newNodeToProcess)
{
    //start location is the exclusive prefix sum
    int wordChunk = (nodeNum+threadNum-1)/threadNum;
    int beg = threadId * wordChunk;
    int end = (beg+wordChunk<nodeNum) ? beg+wordChunk : nodeNum; 
    int curr;

    for(curr = beg; curr<=end-1; curr++){
        if(res[nodeToProcess[curr]] == UNMATCHED){
            int offset = startLocations[threadId]++;
            newNodeToProcess[offset] = nodeToProcess[curr];
        }
    }

   
    //This is where you have to set the remaining number of unmatched nodes = UNMATCHED
    /* 
        Vi = the set of vertices assigned to thread i
        for each v in Vi do
            if (res[v] == UNMATCHED) then
                offset = startLocations[i]++
                newNodeToProcess[offset] = v
            end if
        end for
    */
}
