#include "ui.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void ui_printList(const tNumStoreHead *list_head)
{
  tNumStorage *curr=list_head->head;
  printf("count: %d\n", list_head->counts);
  printf("%s", "  From head--> ");
  while (curr!=NULL)
  {
    printf("%d ", curr->number);
    curr=curr->next;
  }
  puts("");
  curr=list_head->tail;
  printf("%s", "  From tail--> ");
  while (curr!=NULL)
  {
    printf("%d ", curr->number);
    curr=curr->previous;
  }
  printf("\n\n");
}

void ui_run_menu(tNumStoreHead *list_head)
{
    int choice;
                                                                                                                                                                                                                                
    while (1)                                                                                                                                                                                                                   
    {                                                                                                                                                                                                                           
        printf("%s", "1. Add a number or 2. Delete a number: ");                                                                                                                                                                
        if (scanf("%d", &choice) != 1 || choice == -1)                                                                                                                                                                          
        {                                                                                                                                                                                                                       
            break;                                                                                                                                                                                                              
        }                                                                                                                                                                                                                       
                                                                                                                                                                                                                                
        if (choice == 1)                                                                                                                                                                                                        
        {                                                                                                                                                                                                                       
            int value;                                                                                                                                                                                                          
            printf("%s", "Add a number: ");                                                                                                                                                                                     
            if (scanf("%d", &value) != 1)                                                                                                                                                                                       
            {                                                                                                                                                                                                                   
                break;                                                                                                                                                                                                          
            }                                                                                                                                                                                                                   
                                                                                                                                                                                                                                
            if (list_head->counts == 0)                                                                                                                                                                                         
            {                                                                                                                                                                                                                   
                insertNum(list_head, value);                                                                                                                                                                                    
            }                                                                                                                                                                                                                   
            else                                                                                                                                                                                                                
            {                                                                                                                                                                                                                   
                int location;                                                                                                                                                                                                   
                int mode;                                                                                                                                                                                                       
                printf("%s", "  Specify a target location ");                                                                                                                                                                   
                if (scanf("%d", &location) != 1)                                                                                                                                                                                
                {                                                                                                                                                                                                               
                    break;                                                                                                                                                                                                      
                }                                                                                                                                                                                                               
                if (location < 1 || location > list_head->counts)                                                                                                                                                               
                {                                                                                                                                                                                                               
                    printf("%s", "error");                                                                                                                                                                                      
                    continue;                                                                                                                                                                                                   
                }                                                                                                                                                                                                               
                                                                                                                                                                                                                                
                printf("%s", "  1. Before or 2. After the location: ");                                                                                                                                                         
                if (scanf("%d", &mode) != 1)                                                                                                                                                                                    
                {                                                                                                                                                                                                               
                    break;                                                                                                                                                                                                      
                }                                                                                                                                                                                                               
                if (mode != 1 && mode != 2)                                                                                                                                                                                     
                {                                                                                                                                                                                                               
                    printf("%s", "error");                                                                                                                                                                                      
                    continue;                                                                                                                                                                                                   
                }                                                                                                                                                                                                               
                                                                                                                                                                                                                                
                tNumStorage *target = get_node_at(list_head, location);                                                                                                                                                         
                tNumStorage *newNode = create_node(value);                                                                                                                                                                      
                if (target == NULL || newNode == NULL)                                                                                                                                                                          
                {                                                                                                                                                                                                               
                    free(newNode);                                                                                                                                                                                              
                    continue;                                                                                                                                                                                                   
                }                                                                                                                                                                                                               
                                                                                                                                                                                                                                
                if (mode == 1)                                                                                                                                                                                                  
                {                                                                                                                                                                                                               
                    insert_before(list_head, target, newNode);                                                                                                                                                                  
                }                                                                                                                                                                                                               
                else                                                                                                                                                                                                            
                {                                                                                                                                                                                                               
                    insert_after(list_head, target, newNode);                                                                                                                                                                   
                }                                                                                                                                                                                                               
            }                                                                                                                                                                                                                   
                                                                                                                                                                                                                                
            puts("");                                                                                                                                                                                                           
            ui_printList(list_head);                                                                                                                                                                                               
        }                                                                                                                                                                                                                       
        else if (choice == 2)                                                                                                                                                                                                   
        {                                                                                                                                                                                                                       
            int location;                                                                                                                                                                                                       
                                                                                                                                                                                                                                
            if (list_head->counts == 0)                                                                                                                                                                                         
            {                                                                                                                                                                                                                   
                printf("%s", "List is empty.");                                                                                                                                                                                 
                continue;                                                                                                                                                                                                       
            }                                                                                                                                                                                                                   
                                                                                                                                                                                                                                
            printf("%s", "  Specify a target location to delete ");                                                                                                                                                             
            if (scanf("%d", &location) != 1)                                                                                                                                                                                    
            {                                                                                                                                                                                                                   
                break;                                                                                                                                                                                                          
            }                                                                                                                                                                                                                   
            if (location < 1 || location > list_head->counts)                                                                                                                                                                   
            {                                                                                                                                                                                                                   
                printf("%s", "error");                                                                                                                                                                                          
                continue;                                                                                                                                                                                                       
            }                                                                                                                                                                                                                   
                                                                                                                                                                                                                                
            delete_at(list_head, location);                                                                                                                                                                                     
            ui_printList(list_head);                                                                                                                                                                                               
        }                                                                                                                                                                                                                       
        else                                                                                                                                                                                                                    
        {                                                                                                                                                                                                                       
            printf("%s", "No such choose!\n");                                                                                                                                                                                  
        }                                                                                                                                                                                                                       
    }                                                                                                                                                                                                                           
}                                                                                                                                                                                                                               
                    