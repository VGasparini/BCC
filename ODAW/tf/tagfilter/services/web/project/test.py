import unittest

from multiprocessing import Process


class TagFilterTest(unittest.TestCase):
    def setUp(self):
        self.server = app.app.test_client()
        self.renew()

    def renew(self):
        self.response = self.server.get("/")
        self.response_str = str(self.response.data.decode("utf-8"))

    def test_00_get_root_route(self):
        """
        Testing if page status code is 200 on root route
        """
        self.assertEqual(200, self.response.status_code, "Should be 200")

    def test_01_empty_tags(self):
        """
        Testing if page has none tags
        """
        self.assertNotIn('name="tag_button"', self.response_str, "Should be empty")

    def test_02_add_tag(self):
        """
        Testing if 'tecnologia' tag are added
        """
        data = {"tag_input": "tecnologia"}
        self.server.post("/", data=data)
        self.renew()
        self.assertIn(
            'name="tag_button"', self.response_str, "Should has 'tecnologia' button tag"
        )

    def test_03_add_duplicated_tag(self):
        """
        Testing if trying to add 'tecnologia' duplicated tag are treated
        """
        data = {"tag_input": "tecnologia"}
        self.server.post("/", data=data)
        self.renew()
        data = {"tag_input": "tecnologia"}
        self.server.post("/", data=data)
        self.renew()
        self.assertEqual(
            1,
            self.response_str.count('name="tag_button" value="tecnologia"'),
            "Shouldn't has two 'tecnologia' buttons",
        )

    def test_04_remove_tag(self):
        """
        Testing remove a tag
        """
        data = {"tag_input": "tecnologia"}
        self.server.post("/", data=data)
        self.renew()
        data = {"tag_button": "tecnologia"}
        self.server.post("/", data=data)
        self.renew()
        self.assertNotIn(
            'name="tag_button"', self.response_str, "Should remove 'tecnologia' tag"
        )


if __name__ == "__main__":
    unittest.main()
