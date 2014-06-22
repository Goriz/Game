using UnityEngine;
using System.Collections;
	
public class GotoMouse : MonoBehaviour
{
	public float speed = 5f;
	private Vector2 target;

	void Start()
	{
		target = transform.position;
	}

	void Update()
	{
		if (Input.GetMouseButton(0))
		{
			target = Camera.main.ScreenToWorldPoint(Input.mousePosition);
		}
		transform.position = Vector2.MoveTowards(transform.position, new Vector2(target.x, target.y), speed * Time.deltaTime);
	}
}

