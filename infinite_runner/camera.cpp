//Items Needed
//Script is Called In Late Update
//Camera Target
//Camera Transform
//Camera Velocity
//Camera Follow Speed

private void Awake()
    {
        cameraTransform = Camera.main.transform;
    }

    // Update is called once per frame
    public void HandleCameraMovement()
    {
        FollowPlayer();
    }

    private void FollowPlayer()
    {
        Vector3 targetPosition = new Vector3(cameraTarget.position.x, (cameraTarget.position.y + 1.3f), cameraTarget.position.z - 3f);
        Vector3 finalPosition = Vector3.SmoothDamp(transform.position, targetPosition, ref cameraFollowVelocity, cameraFollowSpeed);
        transform.position = finalPosition;
    }
