"""
Test Cases for Counter Web Service

Create a service that can keep a track of multiple counters
- API must be RESTful - see the status.py file. Following these guidelines, you can make assumptions about
how to call the web service and assert what it should return.
- The endpoint should be called /counters
- When creating a counter, you must specify the name in the path.
- Duplicate names must return a conflict error code.
- The service must be able to update a counter by name.
- The service must be able to read the counter
"""
import pytest
from src import app
from src import status

@pytest.fixture()
def client():
    """Fixture for Flask test client"""
    return app.test_client()

@pytest.mark.usefixtures("client")
class TestCounterEndpoints:
    """Test cases for Counter API"""

    def test_create_counter(self, client):
        """It should create a counter"""
        result = client.post('/counters/foo')
        assert result.status_code == status.HTTP_201_CREATED

    def test_delete_counter(self, client):
        """It should delete an existing counter"""

        client.post('/counters/my_counter')
        response = client.delete('/counters/my_counter')
        assert response.status_code == status.HTTP_204_NO_CONTENT
        response = client.get('/counters/my_counter')
        assert response.status_code == status.HTTP_404_NOT_FOUND

    def test_create_new_counter(self, client):
        """It should create a counter"""
        result = client.post('/counters/fooo')
        assert result.status_code == status.HTTP_201_CREATED
