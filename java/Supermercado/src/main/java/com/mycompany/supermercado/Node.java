/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.supermercado;

/**
 *
 * @author 57314
 * @param <Object>
 */
public class Node<Object> {
    private Object dato;
    private Node siguiente;
    
    /*Se definen los dos tipos de constructores de la clase node*/
    
    public Node(){
     
    }
    
    public Node(Object elemento){
        this.dato = elemento;
        this.siguiente = null;
    }
    
    /* Se definen los metodos setters and getters de la clase node*/ 
    
    public Object getDato(){
        return this.dato;
    }
    
    public Node getSiguiente(){
        return this.siguiente;
    }
    
    public void setDato(Object elemento) {
        this.dato = elemento;
    }

    public void setSiguiente(Node siguiente) {
        this.siguiente = siguiente;
    }
    
}
