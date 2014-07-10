﻿using UnityEngine;
using System.Collections;

public class Player : MonoBehaviour {
	public GameObject fire;
	private GameObject command;
	private Vector2 tappoint;
	private Animator animator;
	private int ChargeId;
	private bool charge = false;


	// Use this for initialization
	void Start () {
		animator = GetComponent<Animator> ();

		ChargeId = Animator.StringToHash ("Charge");

		command = GameObject.Find("Command");
	}
	
	// Update is called once per frame
	void Update () {
	

		if (Input.GetMouseButtonDown (0)) {
			tappoint = Camera.main.ScreenToWorldPoint(Input.mousePosition);

			Raycast();

			if(charge == false && tappoint.x > -4 && GameObject.Find("MPStar1(Clone)") != null){
			animator.SetTrigger ("Attack");
			Instantiate (fire, transform.position, transform.rotation);
				Destroy(GameObject.Find("MPStar1(Clone)"));
			}
		}

		if (charge == true) {
			animator.SetBool(ChargeId, true);
			command.SetActive(true);
		}else{
			animator.SetBool(ChargeId, false);
			command.SetActive(false);
		}
	}


	public Vector2 getMousePoint(){
		return tappoint;
	}


	void Raycast(){
		Collider2D collition2d = Physics2D.OverlapPoint(tappoint);
		if (collition2d) {
			RaycastHit2D hitObject = Physics2D.Raycast(tappoint,-Vector2.up);
			if (hitObject) {
				Debug.Log("hit object is " + hitObject.collider.gameObject.name);
				if(hitObject.collider.gameObject.name == "Player"){
					if(charge == false){
					charge = true;
					}else charge = false;
				}
			}
		}
	}
}
